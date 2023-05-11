/* !
@file FadeOut.cpp
@brief タイトルシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FadeOut::FadeOut(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	FadeOut::~FadeOut() {}

	void FadeOut::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"FADE_WHITE", false, true, 1);
	}
}
