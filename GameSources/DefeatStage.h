/*!
@file DefeatStage.h
@brief ゲーム失敗時のステージ
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	class DefeatStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateResultSprite();
		//BGMの再生
		void PlayBGM();

		//入力ハンドラー
		InputHandler2<DefeatStage> m_InputHandler;
	public:
		//構築と破棄
		DefeatStage() :Stage() {}
		virtual ~DefeatStage() {}
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