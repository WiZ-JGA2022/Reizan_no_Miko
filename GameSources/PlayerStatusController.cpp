/*!
@file PlayerStatusController.cpp
@brief �v���C���[�̃X�e�[�^�X���Ǘ�����N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_BaseRisingValue(10),
		m_DamageDelayCount(60),
		m_maxHp(50),
		m_maxExp(5),
		m_beforeMaxExp(m_maxExp),
		m_damageDelayFlame(m_DamageDelayCount)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		// �X�e�[�^�X�㏸�l�̏�����
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(0);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// �v���C���[�����Ȃ�������
		if (!player->GetDrawActive())
		{
			// �������~����
			return;
		}

		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		// �o���l�擾�ʂ��K�v�o���l�𒴂����Ƃ�
		if (m_statusValue[L"EXP"] >= m_maxExp)
		{
			// �o���l���x�����グ��
			m_statusLevel[L"EXP"]++;
			// ���x���A�b�v�C�x���g�̎��s
			levelUpEvent->LevelUpEvent();
			// EXP��0�ɖ߂�
			m_statusValue[L"EXP"] = 0;
			// ���񃌃x���A�b�v�܂łɕK�v��EXP�ʂ𑝂₷
			m_maxExp = m_BaseRisingValue * m_statusLevel[L"EXP"];
		}

		// ���x���A�b�v�C�x���g���A�N�e�B�u�Ȃ�
		if (levelUpEvent->GetEventActive())
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice(); 
			auto& pad = device.GetControlerVec()[0]; 

			// �\���L�[�̏�A�E�A���őI��
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(0));
				levelUpEvent->SetEventActive(false);
			}
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(1));
				levelUpEvent->SetEventActive(false);
			}
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(2));
				levelUpEvent->SetEventActive(false);
			}
		}
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
			m_maxHp += m_BaseRisingValue;
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
	} // end StatusLevelUpdate

	// �G����󂯂�_���[�W�̏���
	void PlayerStatusController::PlayerDamageProcess(float damage)
	{
		// �h��͂̌y����ǉ������_���[�W�ʂ̌v�Z
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));
		// �_���[�W�������̗̑͂����炷
		m_statusValue[L"HP"] -= totalDamage;
	} // end PlayerTakenDamage

	float PlayerStatusController::GetStatusValue(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}

	int PlayerStatusController::GetMaxHp()
	{
		return m_maxHp;
	}

	int PlayerStatusController::GetMaxExp()
	{
		return m_maxExp;
	}

	void PlayerStatusController::ExpValueUpdate(int expValue)
	{
		m_statusValue[L"EXP"] += expValue;
	}
}
