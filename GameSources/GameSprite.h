/**
@file GameSprite.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class GameSprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ
		const Vec2 m_AfterSize; // 更新サイズ

		Vec3 m_position; // テクスチャ名

	public:
		// コンストラクタ
		GameSprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~GameSprite();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;

	};
}