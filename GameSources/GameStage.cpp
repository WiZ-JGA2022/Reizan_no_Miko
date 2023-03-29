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

	void GameStage::CreateItem() {

		////Itemオブジェクトの追加
		AddGameObject<Item>(Vec3(0.0f,0.0f,0.0f));

	}


	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		auto player = AddGameObject<PlayerController>();
		SetSharedGameObject(L"Player", player);
	}


	void GameStage::OnCreate() {
		try {

			//AddGameObject<SeekObject>(Vec3(1,0,0));
			auto player = AddGameObject<PlayerController>();
			auto playerK = AddGameObject<Player>();
			AddGameObject<EnemyController>(playerK);


			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			//AddGameObject<PlayerShot>(player);
			CreatePlayer();

			// 地面の作成
			AddGameObject<Field>();

			// ExpバーとHpバーの作成
			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();


			// レベルアップイベントの作成
			AddGameObject<RandomSelectLevelUpButton>();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);

			CreateItem();

			//auto player = AddGameObject<Player>();


			
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnDraw()
	{
		Stage::OnDraw(); // 継承するはずだった親クラスの関数を呼び出す
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}
}
//end basecross
