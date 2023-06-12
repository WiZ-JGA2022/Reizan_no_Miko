/*!
@file TitleStage.h
@brief タイトルステージ
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_bgm; // サウンドアイテム

		bool m_start; // スタートボタンが押されたか

		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();

		//BGMの再生
		void PlayBGM();
		//入力ハンドラー
		InputHandler2<TitleStage> m_inputHandler;
	public:
		// コンストラクタ
		TitleStage() :
			Stage(),
			m_start(false)
		{}
		// デストラクタ
		virtual ~TitleStage() {}

		// 初期化
		virtual void OnCreate()override;
		// 更新
		virtual void OnUpdate()override;
		// 破壊処理
		virtual void OnDestroy() override;
		// Aボタン
		void OnPushA() {
			//何もしない
		}
		// Bボタン
		void OnPushB();

	};

}