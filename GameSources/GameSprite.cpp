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
		Sprites::CreateSeekSizeSprite(m_position, m_DefaultSize, m_AfterSize, L"GAME_SPRITE", SeekType::GameSprite, 0.5f);
	}

	void GameSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}