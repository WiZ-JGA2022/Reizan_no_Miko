/*!
@file FadeIn.h
@brief �t�F�[�h�C���̒�`
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeIn : public Sprites {
		// ��ʂ̃f�t�H���g�T�C�Y
		const Vec2 m_DefaultSize; 
		
		wstring m_texKey; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey);
		// �f�X�g���N�^
		~FadeIn();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};
}
