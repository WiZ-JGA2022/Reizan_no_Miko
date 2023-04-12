/* !
@file ResultSprite.h
@brief リザルトシーンの背景の実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ResultSprite::ResultSprite(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	ResultSprite::~ResultSprite() {}

	void ResultSprite::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		m_vertices = {
			{Vec3(0.0f				, 0.0f				, 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(m_DefaultSize.x	, 0.0f				, 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(0.0f				, -m_DefaultSize.y	, 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(m_DefaultSize.x	, -m_DefaultSize.y	, 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"RESULT");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f);

		// 透過処理を有効にする
		SetAlphaActive(true);
	}
}