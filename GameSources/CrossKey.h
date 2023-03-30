/*!
@file CrossKey.h
@brief �\���L�[�̕\���Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CrossKeySprites : public GameObject {
	private:
		bool m_Alpha;         // �����t���O
		Vec2 m_DefaultScale;    // �傫��
		Vec2 m_DefaultPos;      // �ʒu
		int m_TextureNum;	  // �e�N�X�`���ԍ�
		wstring m_TextureKey; // �e�N�X�`��
		int m_TexNum;
		float m_AlphaNum = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
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
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CrossKeySprites() {}
		//--------------------------------------------------------------------------------------
		/**
		@brief�@������
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/**
		@brief�@�X�V
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;

		wstring ControllerNum(int i);
	};
}
//end basecross