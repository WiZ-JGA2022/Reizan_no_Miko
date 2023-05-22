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
			Wait,		// 待機
			Stop,		// 終了
			SizeChange	// 実行
		};

		enum RBSeekSizeState m_isSeekSizeState = RBSeekSizeState::Wait; // サイズ変更の状態
		enum SeekType m_seekType = SeekType::BottomRight; // 変化する方向
	public:
		RBButtonSprite(const shared_ptr<Stage>& stage);
		~RBButtonSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}

