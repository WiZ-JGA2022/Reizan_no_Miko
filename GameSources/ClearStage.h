/*!
@file ClearStage.h
@brief ゲームクリア時のステージ
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	クリアステージクラス
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {
		shared_ptr<SoundItem> m_bgm;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateResultSprite();
		//BGMの再生
		void PlayBGM();

		//入力ハンドラー
		InputHandler2<ClearStage> m_inputHandler;
	public:
		// コンストラクタ
		ClearStage() :Stage() {}
		// デストラクタ
		virtual ~ClearStage() {}
		// 初期化
		virtual void OnCreate()override;
		// 更新
		virtual void OnUpdate()override;
		// 破壊処理
		virtual void OnDestroy() override;
		//Aボタン
		void OnPushA() {
			//何もしない
		}
		//Bボタン
		void OnPushB();

	};
}
