/*!
@file RightStick.h
@brief �ϋv�l�X�v���C�g
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class RightStick : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

		wstring m_texKey; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		RightStick(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~RightStick();

		void OnCreate() override; // ������ 
	};
}
