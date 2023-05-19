/**
@file GameSprite.cpp
@brief •¶Žš‚Ì•\Ž¦‚ÌŽÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameSprite::GameSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight() / 4)),
		m_AfterSize(Vec2(384.0f, 64.0f))
	{
	}
	GameSprite::~GameSprite() {}

	void GameSprite::OnCreate()
	{
		m_position = Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f);
		Sprites::CreateSprite(m_position, m_DefaultSize, L"GAME_SPRITE");
	}

	void GameSprite::OnUpdate()
	{
		Sprites::UpdateSeekSizeSprite(m_AfterSize, 0.5f, SeekType::GameSprite, 0.5f);
	}
}