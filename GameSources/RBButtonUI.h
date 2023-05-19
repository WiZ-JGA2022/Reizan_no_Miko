/* !
@file RBButtonUI.h
@brief RBButtonUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class RBButtonSprite : public Sprites {
		const Vec2 m_DefaultSize;
		const Vec2 m_AfterSize;
		const WORD RB_BUTTON = XINPUT_GAMEPAD_RIGHT_SHOULDER;

		enum class RBSeekSizeState
		{
			Wait,		// �ҋ@
			Stop,		// �I��
			SizeChange	// ���s
		};

		enum RBSeekSizeState m_isSeekSizeState = RBSeekSizeState::Wait; // �T�C�Y�ύX�̏��
		enum SeekType m_seekType = SeekType::BottomRight; // �ω��������
	public:
		RBButtonSprite(const shared_ptr<Stage>& stage);
		~RBButtonSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}

