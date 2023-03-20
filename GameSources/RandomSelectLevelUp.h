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
		int m_PlayCommandCount = 1;		//!
		bool ControllerSprite = true;

		/**
		* A～Xボタン、上下左右ボタンに割り当てられている数字をランダムに設定
		*
		* @param なし
		*
		* @return commandnum : 0x0000で割り当てられているpadのボタンの数字情報
		*/
		int CommandNum();
		/**
		* コマンドの回数を指定
		*
		* @param なし
		*
		* @return commandnum : 0x0000で割り当てられているpadのボタンの数字情報
		*/
		void CommandCount(int maxC);

	public :
		RandomSelectLevelUp(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return ControllerSprite;
		}

		virtual ~RandomSelectLevelUp();

		virtual void OnCreate() override;
	};

}
//end basecross
