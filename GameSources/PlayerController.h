/*!
@file PlayerController.h
@brief プレイヤーキャラ
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class PlayerController : public GameObject
	{
		// プレイヤーの操作に使用するボタン
		const WORD BUTTON_HOMING = XINPUT_GAMEPAD_LEFT_SHOULDER;
		const WORD BUTTON_BARRIER = XINPUT_GAMEPAD_RIGHT_SHOULDER;

	public:
		PlayerController(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // オブジェクトの初期設定用の関数
		void OnUpdate() override; // オブジェクトデータの更新

	};
}
