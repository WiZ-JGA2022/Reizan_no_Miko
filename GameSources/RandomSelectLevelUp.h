/*!
@file RandomSelectLevelUpButton.h
@brief ランダムにレベルアップできる項目を出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUpButton : public GameObject
	{
		Vec3 m_Scale;					// 大きさ
		Vec3 m_Rotation;				// 角度
		Vec3 m_Position;				// 位置

		// レベルアップ時に表示するボタンの数
		static const int m_PickUpStatusCount = 3;

		int m_CommandCount = 0;		// コマンドの回数
		int m_CommandNums[m_PickUpStatusCount] = { 0 };	// ボタンのの数字を保存しておく用

		bool m_CommandFlg = true;		
		bool m_CreateStateFlg = false;	
		bool m_ControllerSprite = true;

		/**
		* 強化できるステータス・強化できる武器をランダムに指定
		*
		* @param selectStatus 強化可能なステータス・武器の総数
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return m_ControllerSprite;
		}

		virtual ~RandomSelectLevelUpButton();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void LevelUpEvent();
	};

}
//end basecross
