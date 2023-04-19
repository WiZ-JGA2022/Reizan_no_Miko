/* !
@file TrapUI.h
@brief �g���b�vUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class TrapSprite : public GameObject {
	private:
		bool m_alpha;         // �����t���O
		Vec2 m_defaultScale;    // �傫��
		Vec2 m_defaultPos;      // �ʒu
		int m_textureNum;	  // �e�N�X�`���ԍ�
		wstring m_textureKey; // �e�N�X�`��
		int m_texNum;
		float m_alphaNum = 1.0f;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		TrapSprite(const shared_ptr<Stage>& stagePtr,
			const int& m_textureNum,
			bool trace,
			const Vec2& startScale,
			const Vec2& startPos,
			const int& texNum
		);
		//--------------------------------------------------------------------------------------
		/**
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TrapSprite() {}
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