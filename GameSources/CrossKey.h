/*!
@file CrossKey.h
@brief 十字キーの表示など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CrossKeySprites : public GameObject {
	private:
		bool m_alpha;         // 透明フラグ
		Vec2 m_defaultScale;    // 大きさ
		Vec2 m_defaultPos;      // 位置
		int m_textureNum;	  // テクスチャ番号
		wstring m_textureKey; // テクスチャ
		int m_texNum;
		float m_alphaNum = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		CrossKeySprites(const shared_ptr<Stage>& StagePtr,
			const int& m_textureNum,
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