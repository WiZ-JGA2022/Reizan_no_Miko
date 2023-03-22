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

	void GameStage::OnCreate() {
		try {
			auto& app = App::GetApp();

			auto mediaPath = app->GetDataDirWString();
			auto texturePath = mediaPath + L"Textures/";

			app->RegisterTexture(L"EXPBAR_BLACK", texturePath + L"ExpBar(Black).png");
			app->RegisterTexture(L"EXPBAR_BLUE", texturePath + L"ExpBar(Blue).png");
			app->RegisterTexture(L"HPBAR_GREEN", texturePath + L"HpBar(Green).png");
			app->RegisterTexture(L"HPBAR_RED", texturePath + L"HpBar(Red).png");

			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
