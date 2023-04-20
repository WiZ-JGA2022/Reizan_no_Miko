/*!
@file ButtonSelect.h
@brief 複数のボタンUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ButtonSelect : public GameObject
	{
		// レベルアップ時に表示するボタンの数
		static const int m_PickUpStatusCount = 4;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// ボタンの数字を保存しておく用

		bool m_isActiveSprite = false;

	public:
		ButtonSelect(const shared_ptr<Stage>& StagePtr);
		~ButtonSelect();

		virtual void OnCreate() override;




		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross


