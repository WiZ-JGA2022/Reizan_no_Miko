/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < statusName.size(); i++)
		{
			status.emplace_back(0);
			status[i] = statusValue[statusName[i]] + (statusLevel[statusName[i]] * MAGNIFICATION);

		}
		maxHp = statusValue[statusName[0]] + (statusLevel[statusName[0]] * MAGNIFICATION);
	}

	void PlayerStatusController::OnUpdate()
	{
		//if (player == null)
		//{
		//	return;
		//}
		//expCount = expItem.GetExpCount(); // ���݌o���l���擾

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
		m_maxExp = 10 * (m_expLevel - 1) + m_previousExp;

		// //HP��0�ɂȂ�����
		//if (status[0] < 0)
		//{
		//	GetStage()->RemoveGameObject<PlayerShot>(GetThis<PlayerShot>());
		//	GetStage()->RemoveGameObject<PlayerController>(GetThis<PlayerController>());

		//}
	}
	void PlayerStatusController::StatusLevelUpdate(int selectStatusNum)
	{
		// ���x�����グ��
		statusLevel[statusName[selectStatusNum]]++;
		//�X�e�[�^�X�㏸�l�𔽉f����
		status[selectStatusNum] += MAGNIFICATION;
		//auto player = GetComponent<PlayerController>()->PlayerSpeedUp(status[3]);
		//GetComponent<PlayerShot>(LevelUpShotDelay(status[4]));
		//if (selectStatusNum == 0)
		//{
		//	//maxHp += MAGNIFICATION;
		//}
		// �o���l��0�ɖ߂�
		//expItem.ResetExpCount();
		//// ���x���A�b�v�C�x���g�̏I��
		//levelUpPanel.GetComponent<LevelUpEvent>().PanelUnActivated();

	} // end StatusLevelUpdate

	// �G����󂯂�_���[�W�̏���
	void PlayerTakenDamage()
	{
		// �}�W�b�N�i���o�[�̕�������X�G�̍U���͂ɕύX����
		float enemyATK = 1.0f;

		// �G�̍U���͕������̗̑͂����炷
		//status[0] -= enemyATK;
	} // end PlayerTakenDamage

}
