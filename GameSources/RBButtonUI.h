/* !
@file RBButtonUI.h
@brief RBButtonUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class RBButtonSprite : public Sprites {
		const Vec2 m_DefaultSize; //初期サイズ
		const Vec2 m_AfterSize;  //変更五のサイズ
		const WORD RB_BUTTON = XINPUT_GAMEPAD_RIGHT_SHOULDER;  //ゲームパッドのRBボタンの取得

		bool m_startSe;  //SEなっているか

		enum class RBSeekSizeState
		{
			Wait,		// 待機
			Stop,		// 終了
			SizeChange	// 実行
		};

		enum RBSeekSizeState m_isSeekSizeState = RBSeekSizeState::Wait; // サイズ変更の状態
		enum SeekType m_seekType = SeekType::BottomRight; // 変化する方向
	public:
		//コンストラクタ
		RBButtonSprite(const shared_ptr<Stage>& stage);
		//デスとラクタ
		~RBButtonSprite();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

	};
}

