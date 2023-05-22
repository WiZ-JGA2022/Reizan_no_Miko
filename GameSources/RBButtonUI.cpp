/* !
@file RBButtonUI.cpp
@brief RBButtonUI‚ÌŽÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RBButtonSprite::RBButtonSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f)),
		m_AfterSize(Vec2(170.0f, 170.0f))
	{
	}
	RBButtonSprite::~RBButtonSprite() {}

	void RBButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 350.0f, 0.0f), m_DefaultSize, L"RB_BUTTON");
	}

	void RBButtonSprite::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		if (pad.wButtons & RB_BUTTON)
		{
			SetSeekSizeState(0);
			Sprites::UpdateSeekSizeSprite(m_AfterSize,10.0f, SeekType::UpperRight);
			return;
		}
		else
		{
			SetSeekSizeState(0);
			Sprites::UpdateSeekSizeSprite(m_DefaultSize, 0.1f, SeekType::UpperRight);
		}
	}
}
