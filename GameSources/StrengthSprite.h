/*!
@file StrengthSprite.h
@brief 耐久値スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class StrengthSprite : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

		wstring m_texKey; // テクスチャ名

	public:
		// コンストラクタ
		StrengthSprite(const shared_ptr<Stage>& stage);
		// デストラクタ
		~StrengthSprite();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理
	};
}
