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
		if ((pad.wPressedButtons && RB_BUTTON) && (m_isSeekSizeState != RBSeekSizeState::Stop))
		{
			m_isSeekSizeState = RBSeekSizeState::SizeChange;
			Sprites::OnUpdate();
		}
	}
}
