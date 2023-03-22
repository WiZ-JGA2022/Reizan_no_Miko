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
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f, 1.0f ,0.0f);

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

			auto& app = App::GetApp();

			auto mediaPath = app->GetDataDirWString();
			auto texturePath = mediaPath + L"Textures/";

			app->RegisterTexture(L"EXPBAR_BLACK", texturePath + L"ExpBar(Black).png");
			app->RegisterTexture(L"EXPBAR_BLUE", texturePath + L"ExpBar(Blue).png");
			app->RegisterTexture(L"HPBAR_GREEN", texturePath + L"HpBar(Green).png");
			app->RegisterTexture(L"HPBAR_RED", texturePath + L"HpBar(Red).png");

			CreateSeekObject();
			CreatePlayer();
			//AddGameObject<SeekObject>(Vec3(1,0,0));

			auto player = AddGameObject<PlayerController>();


			//ビューとライトの作成
			CreateViewLight();

			// ExpバーとHpバーの作成
			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();

			// 地面の作成
			AddGameObject<Field>();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			if (maincamera) // エラーチェック
			{
				maincamera->SetTarget(player);
			}

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
