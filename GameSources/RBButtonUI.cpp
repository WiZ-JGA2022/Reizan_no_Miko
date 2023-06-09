/* !
@file RBButtonUI.cpp
@brief RBButtonUIの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	RBButtonSprite::RBButtonSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f)),
		m_AfterSize(Vec2(170.0f, 170.0f)),
		m_startSe(false)
	{
	}
	// デストラクタ
	RBButtonSprite::~RBButtonSprite() {}

	// 初期化
	void RBButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 350.0f, 0.0f), m_DefaultSize, L"RB_BUTTON");
	}

	// 更新処理
	void RBButtonSprite::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		if (pad.wButtons & RB_BUTTON)
		{
			if (!m_startSe)
			{
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"SKIP_SE", 0, 0.3f);
				m_startSe = true;
			}
			SetSeekSizeState(0);
			Sprites::UpdateSeekSizeSprite(m_AfterSize,10.0f, SeekType::UpperRight);
			return;
		}
		else
		{
			m_startSe = false;
			SetSeekSizeState(0);
			Sprites::UpdateSeekSizeSprite(m_DefaultSize, 0.1f, SeekType::UpperRight);
		}
	}
}
