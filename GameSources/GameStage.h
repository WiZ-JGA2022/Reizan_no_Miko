/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"
#include "TrapUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		const float m_TotalTimeSeconds = 600.0f;

		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		// 敵の作成
		void CreateEnemy();
		// レベルアップイベントの作成
		void CreateLevelUpEvent();
		// 主人公の作成
		void CreatePlayer();
		// UIの作成
		void CreateUI();
		//BGMの再生
		void PlayBGM();

		// プレイヤーコンポーネント
		shared_ptr<PlayerController> m_player;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		const float m_TotalTimeSeconds = 10.0f;

		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		// レベルアップイベントの作成
		void CreateLevelUpEvent();
		// 主人公の作成
		void CreatePlayer();
		// UIの作成
		void CreateUI();
		//BGMの再生
		void PlayBGM();

		// プレイヤーコンポーネント
		shared_ptr<PlayerController> m_player;
		shared_ptr<TrapSprite> m_trap;

	public:
		//構築と破棄
		StandbyStage() :Stage() {}
		virtual ~StandbyStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする
	};

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//BGMの再生
		void PlayBGM();
		//入力ハンドラー
		InputHandler2<TitleStage> m_InputHandler;
	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		virtual void OnDestroy() override;
		//Aボタン
		void OnPushA() {
			//何もしない
		}
		//Bボタン
		void OnPushB();

	};

	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateResultSprite();
		//BGMの再生
		void PlayBGM();

		//入力ハンドラー
		InputHandler2<ResultStage> m_InputHandler;
	public:
		//構築と破棄
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

		virtual void OnDestroy() override;
		//Aボタン
		void OnPushA() {
			//何もしない
		}
		//Bボタン
		void OnPushB();

	};

}
//end basecross

