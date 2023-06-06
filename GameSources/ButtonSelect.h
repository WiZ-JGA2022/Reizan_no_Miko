/*!
@file ButtonSelect.h
@brief 複数のボタンUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ButtonSelect : public GameObject
	{
		
		static const int m_PickUpStatusCount = 2; // 表示するボタンの数

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// ボタンの数字を保存しておく用

	public:
		//コンストラクタ
		ButtonSelect(const shared_ptr<Stage>& StagePtr);
		//デストラクタ
		~ButtonSelect();

	
		//初期化
		virtual void OnCreate() override;

	};
}
//end basecross


