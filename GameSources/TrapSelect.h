/*!
@file TrapSelect.h
@brief トラップを選ぶUI
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapSelect : public GameObject
	{
		static const int m_PickUpStatusCount = 2;// 表示するトラップの数

	public:
		// コンストラクタ
		TrapSelect(const shared_ptr<Stage>& StagePtr);
		// デストラクタ
		~TrapSelect();

		//初期化
		virtual void OnCreate() override;
	};
}
//end basecross
