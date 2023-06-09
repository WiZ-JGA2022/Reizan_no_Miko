/* !
@file StartbuttonUI.h
@brief タイトルシーンのボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(550.0f, 64.0f)),
		m_changeSpeed(false)
	{
	}
	// デストラクタ
	StartSprite::~StartSprite() {}

	// 初期化
	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-275.0f,-200.0f, 0.0f), m_DefaultSize, L"START_UI");
	}

	// 更新処理
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