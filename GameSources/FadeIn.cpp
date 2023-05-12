/* !
@file FadeIn.cpp
@brief フェードインの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FadeIn::FadeIn(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	FadeIn::~FadeIn() {}

	void FadeIn::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"FADE_BLACK", false, true, 2);
	}
}