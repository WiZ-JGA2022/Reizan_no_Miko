/*!
@file RandomSelectLevelUpButton.cpp
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X�̎���
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	RandomSelectLevelUpButton::RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end �R���X�g���N�^

	RandomSelectLevelUpButton::~RandomSelectLevelUpButton()
	{
	} // end �f�X�g���N�^

	void RandomSelectLevelUpButton::OnCreate()
	{
	} // end OnCreate

	void RandomSelectLevelUpButton::RandomSelect(int selectStatus)
	{
		int i, j; // ���[�v�p�ϐ�
		int commandNum[m_PickUpStatusCount] = { 0 }; // �����i�[�p�z��
		srand((unsigned int)time(NULL));

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do { // �d��������
				
				commandNum[i] =	rand() % selectStatus;
				for (j = 0; j < i; j++)
				{
					if (commandNum[i] == commandNum[j])
					{
						break;
					}
				}
			} while (i != j);
			m_CommandNums[i] = commandNum[i];
			GetStage()->AddGameObject<LevelUpSprites>(m_CommandNums[i], true, Vec2(516.0f, 192.0f), Vec2(250.0f, 300.0f + -(i * 192.0f) + -(i * 20)), i);
		}
	} // end RandomSelect

	void RandomSelectLevelUpButton::OnUpdate()
	{
		/* �v���C���[�̃X�e�[�^�X����exp�̎擾�ʂ��擾
		* �擾����exp����萔�𒴂�������RandomSelect�����s
		*/

		// �e�X�g�p //
		auto& app = App::GetApp();
		// �Q�[���p�b�h���g�p����
		auto device = app->GetInputDevice(); // �C���v�b�g�f�o�C�X�I�u�W�F�N�g���擾����
		auto& pad = device.GetControlerVec()[0]; // �P�ڂ̃R���g���[���[�̏�Ԃ��擾����

		// �e�X�g�p��B�{�^���Ń��x���A�b�v�C�x���g�����s
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			ControllerSprite = true;

			RandomSelect(8);
		}

		// �\���L�[�̏�A�E�A���őI��
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			ControllerSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			ControllerSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			ControllerSprite = false;
		}
	}
}
//end basecross
