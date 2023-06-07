/* !
@file ResultSprite.h
@brief リザルトシーンの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ResultSprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		ResultSprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~ResultSprite();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理

	};
			
	class ClearSprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

	public:
		// コンストラクタ
		ClearSprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~ClearSprite();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理

	};
}