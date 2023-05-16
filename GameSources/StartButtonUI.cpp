/* !
@file StartbuttonUI.h
@brief タイトルシーンのボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(250.0f, 250.0f))
	{
	}
	StartSprite::~StartSprite() {}

	void StartSprite::OnCreate()
	{
		Sprites::CreateColorChangeSprite(Vec3(50,-100, 0.0f), m_DefaultSize, L"START_UI");
	}

	void StartSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}