/**
@file StandbySprite.cpp
@brief 文字の表示の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	StandbySprite::StandbySprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(384.0f, 64.0f))
	{
	}
	// デストラクタ
	StandbySprite::~StandbySprite() {}

	// 初期化
	void StandbySprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(260.0f, App::GetApp()->GetGameHeight() * 0.5f, 0.0f), m_DefaultSize, L"STANDBY_PHASE");
	}

	// 更新処理
	void StandbySprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}