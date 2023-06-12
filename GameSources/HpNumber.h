/**
@file HpNumber.h
@brief 現在HPと最大HPを数字で表示するUI
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class HpNumber : public GameObject {
		
		const Vec2 m_Size = Vec2(12.0f, 24.0f); // 初期サイズ
		
		int m_place; // 

		float m_maxHp; // 

		// スプライトの元になる頂点データ
		vector<shared_ptr<NumberUI>> m_numbers;

	public :
		// コンストラクタ
		HpNumber(const shared_ptr<Stage>& stage);
		// デストラクタ
		~HpNumber();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理
		void OnDraw() override; // 描画処理

		void UpdateValue(int maxHp, float currentHp); // 
	};
}