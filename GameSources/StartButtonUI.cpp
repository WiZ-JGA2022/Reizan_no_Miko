/* !
@file StartbuttonUI.h
@brief タイトルシーンのボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	StartSprite::~StartSprite() {}

	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"START_UI");
	}
}