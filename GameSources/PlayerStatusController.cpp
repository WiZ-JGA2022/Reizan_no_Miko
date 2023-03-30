/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void PlayerStatusController::OnCreate()
	{

		//for (int i = 0; i < nameKeyList; i++)
		//{
		//	status->size();
		//	status[i] = statusValue[nameKeyList[i]] + (statusLevel[levelKeyList[i]] * MAGNIFICATION);

		//}
		maxHp = statusValue[nameKeyList[0]] + (statusLevel[levelKeyList[0]] * MAGNIFICATION);
	}

	void PlayerStatusController::OnUpdate()
	{
		//if (player == null)
		//{
		//	return;
		//}
		//expCount = expItem.GetExpCount();
		if (m_expCount >= m_maxExp)
		{
			m_previousExp = m_maxExp;

			m_expLevel++;
			//levelUpPanel.GetComponent<LevelUpEvent>().PanelActivated();
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
	void PlayerStatusController::StatusLevelUpdate()
	{
		int rndSelect;
		// ���x�����グ��
		//statusLevel[rndSelect]++;
		//�X�e�[�^�X�㏸�l�𔽉f����
		//status[rndSelect] += MAGNIFICATION;
		//auto player = GetComponent<PlayerController>()->PlayerSpeedUp(status[3]);
		//GetComponent<PlayerShot>(LevelUpShotDelay(status[4]));
		//if (rndSelect == 0)
		//{
		//	//smaxHp += MAGNIFICATION;
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
