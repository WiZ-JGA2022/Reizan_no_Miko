/*!
@file RandomSelectLevelUpButton.h
@brief ランダムにレベルアップできる項目を出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapSelect : public GameObject
	{
		// レベルアップ時に表示するボタンの数
		static const int m_PickUpStatusCount = 4;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// ボタンの数字を保存しておく用

		bool m_isActiveSprite = false;

		/**
		* 強化できるステータス・強化できる武器をランダムに指定
		*
		* @param selectStatus 強化可能なステータス・武器の総数
		*/

	public:
		TrapSelect(const shared_ptr<Stage>& StagePtr);
		~TrapSelect();

		virtual void OnCreate() override;

		/**
		* レベルアップ時に呼ばれる関数
		*/




		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross
