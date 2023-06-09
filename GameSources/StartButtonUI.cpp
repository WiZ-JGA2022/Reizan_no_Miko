/* !
@file StartbuttonUI.h
@brief �^�C�g���V�[���̃{�^���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(550.0f, 64.0f)),
		m_changeSpeed(false)
	{
	}
	// �f�X�g���N�^
	StartSprite::~StartSprite() {}

	// ������
	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-275.0f,-200.0f, 0.0f), m_DefaultSize, L"START_UI");
	}

	// �X�V����
	void StartSprite::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			m_changeSpeed = true;
		}

		Sprites::UpdateFlashingSprite(2, 30, m_changeSpeed);
	}
}