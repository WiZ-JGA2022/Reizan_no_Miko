/**
@file TrapNumber.h
@brief 罠を置ける数を数字で表示するUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TrapNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f); // 初期サイズ

		int m_place; // 桁

		vector<shared_ptr<NumberUI>> m_numbers[4]; // ナンバーオブジェクト

	public:
		// コンストラクタ
		TrapNumber(const shared_ptr<Stage>& stage);
		// デストラクタ
		~TrapNumber();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
		// 描画処理
		void OnDraw() override;

		/**
		* 数字の更新処理
		* 
		* @param trapLimit 罠の上限の取得 		
		* @param currentTrapCount 今おいてるトラップの数
		* @param index 更新したい指数
		* 
		**/
		void UpdateValue(int trapLimit, int currentTrapCount, int index);
	};
}
