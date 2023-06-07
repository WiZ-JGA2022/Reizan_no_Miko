/*!
@file StrengthSprite.h
@brief �ϋv�l�X�v���C�g
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class StrengthSprite : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

		wstring m_texKey; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		StrengthSprite(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~StrengthSprite();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����
	};
}
