/**
@file StandbySprite.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StandbySprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		StandbySprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~StandbySprite();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理

	};
}