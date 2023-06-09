/* !
@file StartbuttonUI.h
@brief �^�C�g���V�[���̃X�^�[�g�{�^���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�R���X�g���N�^�ƃf�X�g���N�^
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(550.0f, 64.0f)),
		m_changeSpeed(false)
	{
	}
	StartSprite::~StartSprite() {}
	//�I��

	//������
	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-275.0f,-200.0f, 0.0f), m_DefaultSize, L"START_UI");	//�ʒu���W�A�����T�C�Y�A�\�[�X�摜
	}

	//�X�V����
	void StartSprite::OnUpdate()
	{
		//�Q�[���p�b�h�̎擾
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)	//����B�{�^���������ꂽ��
		{
			m_changeSpeed = true;	//�_�ŃX�s�[�h�̕ύX��true�ɂ���
		}

		Sprites::UpdateFlashingSprite(2, 30, m_changeSpeed);	//�����_�ŃX�s�[�h�A�ύX��̓_�ŃX�s�[�h
	}
}