/*!
@file LevelUpSprites.h
@brief LevelUpイベント中に出す画像
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LevelUpSprites : public GameObject {
	private:
		bool m_alpha;         // 透明フラグ
		Vec2 m_defaultScale;    // 大きさ
		Vec2 m_defaultPos;      // 位置
		int m_textureNum;	  // テクスチャ番号
		wstring m_textureKey; // テクスチャ
		int m_texNum;
		float m_alphaNum = 1.0f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		LevelUpSprites(const shared_ptr<Stage>& stagePtr,
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
		virtual ~LevelUpSprites() {}
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

		wstring ControllerNum(int i);
	};
}
//end basecross