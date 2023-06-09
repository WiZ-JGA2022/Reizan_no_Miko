/* !
@file HoldSkip.cpp
@brief HoldSkipの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	HoldSkipSprite::HoldSkipSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f))
	{
	}
	// デストラクタ
	HoldSkipSprite::~HoldSkipSprite() {}

	// 初期化
	void HoldSkipSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 300.0f, 0.0f), m_DefaultSize, L"HOLDDOWN_SKIP");
	}
}
