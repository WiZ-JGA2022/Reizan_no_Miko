/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//追いかけるオブジェクトの作成
		void CreateSeekObject();
		//プレイヤーの作成
		void CreatePlayer();


	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//プレイヤーの作成
		void CreatePlayer();
		void CreateItem();
		//初期化
		virtual void OnCreate() override;

		virtual void OnDraw() override; // デバッグ文字用に上書きする


	};


}
//end basecross

