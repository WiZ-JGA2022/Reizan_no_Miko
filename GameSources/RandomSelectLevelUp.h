/*!
@file RandomSelectLevelUpButton.h
@brief ランダムにレベルアップできる項目を出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUpButton : public GameObject
	{
		// レベルアップ時に表示するボタンの数
		static const int m_PickUpStatusCount = 3;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// ボタンの数字を保存しておく用

		bool m_isActiveSprite = false;

		/**
		* 強化できるステータス・強化できる武器をランダムに指定
		*
		* @param selectStatus 強化可能なステータス・武器の総数
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr);
		~RandomSelectLevelUpButton();

		virtual void OnCreate() override;

		/**
		* レベルアップ時に呼ばれる関数
		*/
		void LevelUpEvent();

		bool GetEventActive() 
		{
			return m_isActiveSprite;
		}

		void SetEventActive(bool active)
		{
			m_isActiveSprite = active;
		}

		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross
