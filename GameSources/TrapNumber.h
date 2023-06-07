/**
@file TrapNumber.h
@brief 罠を置ける数を数字で表示するUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TrapNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place;

		float m_maxHp;

		// スプライトの元になる頂点データ
		vector<shared_ptr<NumberUI>> m_numbers[4];

	public:
		// コンストラクタ
		TrapNumber(const shared_ptr<Stage>& stage);
		// デストラクタ
		~TrapNumber();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理
		void OnDraw() override; // 描画処理

		void UpdateValue(int trapLimit, int currentTrapCount, int index);
	};
}
