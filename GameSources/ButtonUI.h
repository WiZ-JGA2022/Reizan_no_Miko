/* !
@file ButtonUI.h
@brief ボタンUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class ButtonSprite : public GameObject {
	private:
		bool m_alpha;         // 透明フラグ
		Vec2 m_defaultScale;    // 大きさ
		Vec2 m_defaultPos;      // 位置
		int m_textureNum;	  // テクスチャ番号
		wstring m_textureKey; // テクスチャ
		float m_alphaNum = 1.0f; // 
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		ButtonSprite(const shared_ptr<Stage>& stagePtr,
			const int& m_textureNum,
			bool trace,
			const Vec2& startScale,
			const Vec2& startPos,
			const int& texNum
		);
		//--------------------------------------------------------------------------------------
		/**
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ButtonSprite() {}
		//--------------------------------------------------------------------------------------
		/**
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/**
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;

		/**
		*　表示する画像の取得
		*
		* @param i トラップの数
		*
		**/
		wstring ControllerNum(int i);
	};
}
//end basecross