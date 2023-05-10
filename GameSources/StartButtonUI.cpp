/* !
@file StartbuttonUI.h
@brief タイトルシーンのボタンの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float m_startScaleZ = 1.0f;// 大きさ
	constexpr float m_startPosZ = 1.0f;	 // 奥行き
	constexpr float m_helfSize = 0.5f;	 // 半分の大きさ


	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	StartSprite::~StartSprite() {}

	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(50,-100, 0.0f), m_DefaultSize, L"START_UI",true,false);
	}
}