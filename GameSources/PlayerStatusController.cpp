/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include <map>

namespace basecross {
	std::map<std::string, float> status;
	float maxHp;

	void PlayerStatusController::OnCreate()
	{
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

		// HP��0�ɂȂ�����
		//if (status[0] < 0)
		//{
			// �v���C���[������
			//player.GetComponent<PlayerController>().DestroyPlayer();
		//}
	}
	void StatusLevelUpdate(int rndSelect)
	{
		// ���x�����グ��
		//statusLevel[]++;
		// �X�e�[�^�X�㏸�l�𔽉f����
		//status[rndSelect] += MAGNIFICATION;
		//player.GetComponent<PlayerController>().PlayerSpeedUp(status[3]);
		//playerShooter.GetComponent<PlayerShot>().LevelUpShotDelay(status[4]);
		//expItem.LevelUpPickUpArea(status[6]);
		//if (rndSelect == 0)
		//{
		//	maxHp += MAGNIFICATION;
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
