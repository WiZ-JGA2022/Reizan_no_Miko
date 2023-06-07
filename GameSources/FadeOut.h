/*!
@file FadeOut.cpp
@brief �t�F�[�h�A�E�g�̒�`
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeOut : public Sprites {
		// ��ʂ̃f�t�H���g�T�C�Y
		const Vec2 m_DefaultSize; 

		wstring m_texKey; //�e�N�X�`����

	public:
		//�R���X�g���N�^
		FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey);
		//�f�X�g���N�^
		~FadeOut();

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;

	};
}

