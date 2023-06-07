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

		bool m_isActiveSprite = false;

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


