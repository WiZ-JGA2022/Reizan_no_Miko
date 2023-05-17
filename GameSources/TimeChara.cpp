/**
@file TimeChara.h
@brief •¶Žš‚Ì•\Ž¦‚ÌŽÀ‘•
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeChara::TimeChara(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(128.0f, 25.6f))
	{
	}
	TimeChara::~TimeChara() {}

	void TimeChara::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-64.0f, App::GetApp()->GetGameHeight() * 0.5f, 0.0f), m_DefaultSize, L"TIME_CHARA");
	}

	void TimeChara::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}