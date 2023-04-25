/* !
@file ResultSprite.h
@brief リザルトシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ResultSprite::ResultSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	ResultSprite::~ResultSprite() {}

	void ResultSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"RESULT");
	}

	ClearSprite::ClearSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	ClearSprite::~ClearSprite() {}

	void ClearSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"CLEAR_SPRITE");
	}
}