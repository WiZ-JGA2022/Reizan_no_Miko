/**
@file TimeChara.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TimeChara : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

	public :
		// コンストラクタ
		TimeChara(const shared_ptr<Stage>& stage);
		// デストラクタ
		~TimeChara();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理


	};
}