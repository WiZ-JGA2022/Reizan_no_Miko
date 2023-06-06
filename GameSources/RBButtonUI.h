/* !
@file RBButtonUI.h
@brief RBButtonUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class RBButtonSprite : public Sprites {
		const Vec2 m_DefaultSize; //�����T�C�Y
		const Vec2 m_AfterSize;  //�ύX�܂̃T�C�Y
		const WORD RB_BUTTON = XINPUT_GAMEPAD_RIGHT_SHOULDER;  //�Q�[���p�b�h��RB�{�^���̎擾

		bool m_startSe;  //SE�Ȃ��Ă��邩

		enum class RBSeekSizeState
		{
			Wait,		// �ҋ@
			Stop,		// �I��
			SizeChange	// ���s
		};

		enum RBSeekSizeState m_isSeekSizeState = RBSeekSizeState::Wait; // �T�C�Y�ύX�̏��
		enum SeekType m_seekType = SeekType::BottomRight; // �ω��������
	public:
		//�R���X�g���N�^
		RBButtonSprite(const shared_ptr<Stage>& stage);
		//�f�X�ƃ��N�^
		~RBButtonSprite();

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;

	};
}

