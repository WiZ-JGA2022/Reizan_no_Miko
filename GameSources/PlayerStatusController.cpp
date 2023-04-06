/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(1);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		m_delayFlame--;

		// �o���l�擾�ʂƕK�v�o���l�������ꍇ(���x���A�b�v����)
		if (m_expCount >= m_maxExp)
		{
			m_previousExp = m_maxExp;

			m_expLevel++;
			auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
			levelUpEvent->LevelUpEvent();
			m_expCount -= m_maxExp;
		}
		// ���񃌃x���A�b�v�܂łɕK�v��EXP�ʂ𑝂₷
		m_maxExp = m_BaseRisingValue * (m_expLevel - 1) + m_previousExp;
	}
	void PlayerStatusController::StatusLevelUpdate(int selectStatusNum)
	{
		// ���x�����グ��
		m_statusLevel[m_statusName[selectStatusNum]]++;
		//�X�e�[�^�X�㏸�l�𔽉f����
		switch (selectStatusNum)
		{
		case 0 : // HP
			// �㏸�l��10(�Œ�l)
			m_statusValue[m_statusName[selectStatusNum]] += m_BaseRisingValue; // �㏸�ʂ̔��f
			break;
		case 1 : // ATK
		case 3 : // SPD
			m_statusRisingValue[selectStatusNum] = 
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 100.0f);	// �㏸�l��0.1(10%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		case 2 : // DEF
		case 4 : // HASTE
			m_statusRisingValue[selectStatusNum] = 
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 1000.0f);	// �㏸�l��0.01(1%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		case 5 : // PICKUP
			m_statusRisingValue[selectStatusNum] = 
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 200.0f);	// �㏸�l��0.05(5%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		default :
			break;
		}
		// �o���l��0�ɖ߂�
		//expItem.ResetExpCount();

	} // end StatusLevelUpdate

	float PlayerStatusController::GetStatusValue(wstring m_statusName)
	{
		return m_statusValue[m_statusName];
	}

	// �G����󂯂�_���[�W�̏���
	void PlayerStatusController::PlayerDamageProcess()
	{
		auto enemy = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		auto& vec = enemy->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				if (shObj->IsUpdateActive()) {
					auto shEnemy = dynamic_pointer_cast<Enemy>(shObj);
					if (shEnemy) {
						m_enemyATK.emplace_back(shEnemy->GetEnemyStatus(L"ATK"));
					}
				}
			}
		}

		// �h��͂̌y����ǉ������_���[�W�ʂ̌v�Z
		float damage = m_enemyATK[0] - (m_enemyATK[0] * (m_statusValue[L"DEF"] - 1.0f));
		if (m_delayFlame <= 0)
		{
			// �_���[�W�������̗̑͂����炷
			m_statusValue[L"HP"] -= damage;
			m_delayFlame = m_DelayCount;
		}
	} // end PlayerTakenDamage

}
