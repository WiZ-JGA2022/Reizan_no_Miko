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
		// テスト用
		void CreateItem();

		// 敵の作成
		void CreateEnemy();

		// レベルアップイベントの作成
		void CreateLevelUpEvent();

		// 主人公の作成
		void CreatePlayer();

		// プレイヤーコンポーネント
		shared_ptr<PlayerController> m_player;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする


	};


}
//end basecross

