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
		const float m_TotalTimeSeconds = 30.0f; // 制限時間

		bool m_isChangeStage;

		shared_ptr<SoundItem> m_bgm;
		// プレイヤーコンポーネント
		shared_ptr<PlayerController> m_player;

		//ビューの作成
		void CreateViewLight();
		// 主人公の作成
		void CreatePlayer();
		// UIの作成
		void CreateUI();
		//BGMの再生
		void PlayBGM();


	public:
		// コンストラクタ
		StandbyStage() :
			Stage(),
			m_isChangeStage(false)
		{}
		// デストラクタ
		virtual ~StandbyStage() {}

		//初期化
		virtual void OnCreate() override;
		// 更新処理
		virtual void OnUpdate() override;
		// 破棄処理
		virtual void OnDestroy() override;
		// 描画処理
		virtual void OnDraw() override;

		// ステージ変更処理
		void ChangeStage();

		bool GetChangingStage()
		{
			return m_isChangeStage;
		}
	};

}