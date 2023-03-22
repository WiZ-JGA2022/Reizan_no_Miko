/*!
@file RandomSelectLevelUp.h
@brief ランダムにレベルアップできる項目を出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUp : public GameObject
	{
		Vec3 m_Scale;					//!大きさ
		Vec3 m_Rotation;				//!角度
		Vec3 m_Position;				//!位置

		int m_CommandCount = 0;		//!コマンドの回数
		vector<int> m_CommandNums;	//!ボタンのの数字を保存しておく用

		bool m_CommandFlg = true;		//!
		bool m_CreateStateFlg = false;	//!
		static const int m_PickUpStatusCount = 3;		//!
		bool ControllerSprite = true;

		/**
		* 強化できるステータス・強化できる武器をランダムに指定
		*
		* @param selectStatus 強化可能なステータス・武器の総数
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUp(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return ControllerSprite;
		}

		virtual ~RandomSelectLevelUp();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
