/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_BGM;

		bool m_start;

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
		TitleStage() :
			Stage(),
			m_start(false)
		{}
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

}