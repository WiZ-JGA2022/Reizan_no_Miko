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
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f, 1.0f ,0.0f);

		auto PtrView = CreateView<SingleView>();
		
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<PlayerController>();
	}		




	void GameStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			auto player = AddGameObject<PlayerController>();
			AddGameObject<PlayerShot>(player);
			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
