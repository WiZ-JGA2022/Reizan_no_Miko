/**
@file StandbySprite.cpp
@brief •¶Žš‚Ì•\Ž¦‚ÌŽÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StandbySprite::StandbySprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	StandbySprite::~StandbySprite() {}

	void StandbySprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(260.0f, App::GetApp()->GetGameHeight() * 0.5f, 0.0f), m_DefaultSize, L"STANDBY_PHASE",false,false);
	}
}