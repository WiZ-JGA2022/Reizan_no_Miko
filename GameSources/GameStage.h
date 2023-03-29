/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		void CreatePlayer();

		shared_ptr<PlayerController> m_player;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		void CreateItem();
		//初期化
		virtual void OnCreate() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする


	};


}
//end basecross

