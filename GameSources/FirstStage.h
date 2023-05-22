/*!
@file FirstStage.h
@brief 第一フェーズステージ
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"
#include "EfkInterface.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class FirstStage : public Stage {
		const float m_TotalTimeSeconds = 240.0f;
		bool m_isOnce = true;

		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		// 敵の作成
		void CreateEnemy();
		// 主人公の作成
		void CreatePlayer();
		// UIの作成
		void CreateUI();
		// エフェクトコントローラーの作成
		void CreateEffectController();
		//BGMの再生
		void PlayBGM();

		// 各種コンポーネント
		shared_ptr<PlayerController> m_player;

	public:
		//構築と破棄
		FirstStage() :Stage() {}
		virtual ~FirstStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする

	};


}
//end basecross

