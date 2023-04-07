/*!
@file CrossKey.h
@brief �\���L�[�̕\���Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CrossKeySprites : public GameObject {
	private:
		bool m_alpha;         // �����t���O
		Vec2 m_defaultScale;    // �傫��
		Vec2 m_defaultPos;      // �ʒu
		int m_textureNum;	  // �e�N�X�`���ԍ�
		wstring m_textureKey; // �e�N�X�`��
		int m_texNum;
		float m_alphaNum = 0.5f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
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