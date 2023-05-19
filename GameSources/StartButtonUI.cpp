/* !
@file StartbuttonUI.h
@brief タイトルシーンのボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(250.0f, 250.0f)),
		m_changeSpeed(false)
	{
	}
	StartSprite::~StartSprite() {}

	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(50,-100, 0.0f), m_DefaultSize, L"START_UI");
	}

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