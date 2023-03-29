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


	//追いかけるオブジェクトの作成
	void GameStage::CreateSeekObject() {
		//オブジェクトのグループを作成する
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		//配列の初期化
		vector<Vec3> vec = {
			{ 0, 0.125f, 10.0f },
			{ 10.0f, 0.125f, 0.0f },
			{ -10.0f, 0.125f, 0.0f },
			{ 0, 0.125f, -10.0f },
		};

		//配置オブジェクトの作成
		for (size_t count = 0; count < vec.size(); count++) {
			auto Ptr = AddGameObject<SeekObject>(vec[count]);
		}

	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}


	void GameStage::OnCreate() {
		try {

			CreateSeekObject();
			CreatePlayer();
			//AddGameObject<SeekObject>(Vec3(1,0,0));

			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			auto player = AddGameObject<PlayerController>();
			//AddGameObject<PlayerShot>(player);

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

			if (maincamera) // エラーチェック
			{
				maincamera->SetTarget(player);
			}

			CreateItem();

			//auto player = AddGameObject<Player>();
			//プレーヤーの作成
			CreatePlayer();


			
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
