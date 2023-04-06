/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_BaseRisingValue(10),
		m_DelayCount(60),
		m_expLevel(1),
		m_expCount(0.0f),
		m_maxExp(10.0f),
		m_previousExp(10.0f),
		m_enemyATK(0),
		m_delayFlame(m_DelayCount)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(0);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (!player->GetDrawActive())
		{
			return;
		}

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

		//wstringstream wss;
		//wss << L"HP : " <<
		//	m_statusValue[L"HP"] << "\n"
		//	<< L"ATK : " <<
		//	m_statusValue[L"ATK"] << "\n"
		//	<< L"DEF : " <<
		//	m_statusValue[L"DEF"] << "\n"
		//	<< L"SPD : " <<
		//	m_statusValue[L"SPD"] << "\n"
		//	<< L"HASTE : " <<
		//	m_statusValue[L"HASTE"] << "\n"
		//	<< L"PICKUP : " <<
		//	m_statusValue[L"PICKUP"] << endl;
		//auto& app = App::GetApp();
		//auto scene = app->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

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
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 100.0f);	// �㏸�l��0.1(10%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		case 2 : // DEF
		case 4 : // HASTE
			m_statusRisingValue[selectStatusNum] = 
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 1000.0f);	// �㏸�l��0.01(1%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		case 5 : // PICKUP
			m_statusRisingValue[selectStatusNum] = 
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 200.0f);	// �㏸�l��0.05(5%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // �㏸�ʂ̔��f
			break;
		default :
			break;
		}
		// �o���l��0�ɖ߂�
		//expItem.ResetExpCount();

	} // end StatusLevelUpdate

	float PlayerStatusController::GetStatusValue(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}

	// �G����󂯂�_���[�W�̏���
	void PlayerStatusController::PlayerDamageProcess()
	{		
		// �h��͂̌y����ǉ������_���[�W�ʂ̌v�Z
		float damage = m_enemyATK - (m_enemyATK * (m_statusValue[L"DEF"] - 1.0f));
		if (m_delayFlame <= 0)
		{
			// �_���[�W�������̗̑͂����炷
			m_statusValue[L"HP"] -= damage;
			m_delayFlame = m_DelayCount;
		}
	} // end PlayerTakenDamage

	void PlayerStatusController::SetEnemyATK(float ATK)
	{
		m_enemyATK = ATK;
	}
}
