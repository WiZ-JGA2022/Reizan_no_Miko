/*!
@file StandbyStage.h
@brief 準備フェーズステージ
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"
#include "PlayerController.h"

namespace basecross {
	class StandbyStage : public Stage {
		const float m_TotalTimeSeconds = 30.0f;

		shared_ptr<SoundItem> m_BGM;

		//ビューの作成
		void CreateViewLight();
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
		StandbyStage() :Stage() {}
		virtual ~StandbyStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		// デバッグ文字列表示用
		virtual void OnDraw() override;
	};

}