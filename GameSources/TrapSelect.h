/*!
@file RandomSelectLevelUpButton.h
@brief ランダムにレベルアップできる項目を出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapSelect : public GameObject
	{
		static const int m_PickUpStatusCount = 2;// 表示するトラップの数

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// トラップを保存しておく用


		/**
		* 強化できるステータス・強化できる武器をランダムに指定
		*
		* @param selectStatus 強化可能なステータス・武器の総数
		*/

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
