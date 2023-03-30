/*!
@file CrossKey.h
@brief 十字キーの表示など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CrossKeySprites : public GameObject {
	private:
		bool m_Alpha;         // 透明フラグ
		Vec2 m_DefaultScale;    // 大きさ
		Vec2 m_DefaultPos;      // 位置
		int m_TextureNum;	  // テクスチャ番号
		wstring m_TextureKey; // テクスチャ
		int m_TexNum;
		float m_AlphaNum = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		CrossKeySprites(const shared_ptr<Stage>& StagePtr,
			const int& m_TextureNum,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			const int& TexNum
		);
		//--------------------------------------------------------------------------------------
		/**
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CrossKeySprites() {}
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