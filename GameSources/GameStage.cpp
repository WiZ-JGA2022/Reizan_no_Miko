/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>(Vec3(0, 0.125f, 0));
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", PlayerPtr);

	}
	void GameStage::CreateItem() {

		////Itemオブジェクトの追加
		AddGameObject<Item>(Vec3(0.0f,0.0f,0.0f));

	}



	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Field>();

			CreateItem();

			//auto player = AddGameObject<Player>();
			//プレーヤーの作成
			CreatePlayer();


			
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
