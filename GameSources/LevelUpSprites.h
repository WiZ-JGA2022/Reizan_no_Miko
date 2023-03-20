/*!
@file LevelUpSprites.h
@brief LevelUpイベント中に出す画像
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LevelUpSprites : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec2 m_StartPos;      //!位置
		int m_TextureNum;	  //!テクスチャ番号
		wstring m_TextureKey; //!テクスチャ
		int m_TexNum;
		float m_Alpha = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		LevelUpSprites(const shared_ptr<Stage>& StagePtr,
			const int& m_TextureNum,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			const int& TexNum
		);
		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~LevelUpSprites() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;

		wstring ControllerNum(int i);
	};
}
//end basecross