/*!
@file FirstStage.h
@brief 第一フェーズステージ
@prod 矢吹悠葉
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
		const float m_TotalTimeSeconds = 120.0f; // 制限時間

		bool m_isChangeStage;

		shared_ptr<SoundItem> m_bgm; // サウンドアイテム
		shared_ptr<PlayerController> m_player; // プレイヤーコンポーネント

		//ビューの作成
		void CreateViewLight();
		// 敵の作成
		void CreateEnemy();
		// 主人公の作成
		void CreatePlayer();
		// UIの作成
		void CreateUI();
		//BGMの再生
		void PlayBGM();

	public:
		// コンストラクタ
		FirstStage() :
			Stage(),
			m_isChangeStage(false)
		{}
		// デストラクタ
		virtual ~FirstStage() {}

		//初期化
		virtual void OnCreate() override;
		// 更新処理
		virtual void OnUpdate() override;
		// 破壊処理
		virtual void OnDestroy() override;
		// 描画処理
		virtual void OnDraw() override; 

		bool GetChangingStage()
		{
			return m_isChangeStage;
		}
	};
}
//end basecross

