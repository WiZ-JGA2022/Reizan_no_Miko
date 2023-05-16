/* !
@file FadeOut.cpp
@brief フェードアウトの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FadeOut::FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight())),
		m_texKey(texKey)
	{
	}
	FadeOut::~FadeOut() {}

	void FadeOut::OnCreate()
	{
		Sprites::CreateFadeSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, m_texKey, 1);
	}

	void FadeOut::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}