/**
@file GameSprite.cpp
@brief •¶Žš‚Ì•\Ž¦‚ÌŽÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameSprite::GameSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	GameSprite::~GameSprite() {}

	void GameSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(280.0f, App::GetApp()->GetGameHeight() * 0.5f, 0.0f), m_DefaultSize, L"GAME_SPRITE");
	}
}