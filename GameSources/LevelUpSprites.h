/*!
@file LevelUpSprites.h
@brief LevelUp�C�x���g���ɏo���摜
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LevelUpSprites : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec2 m_StartPos;      //!�ʒu
		int m_TextureNum;	  //!�e�N�X�`���ԍ�
		wstring m_TextureKey; //!�e�N�X�`��
		int m_TexNum;
		float m_Alpha = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
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
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~LevelUpSprites() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;

		wstring ControllerNum(int i);
	};
}
//end basecross