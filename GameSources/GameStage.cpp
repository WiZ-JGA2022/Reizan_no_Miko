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

	// 敵の作成
	void GameStage::CreateEnemy() {
		CreateSharedObjectGroup(L"EnemyGroup");
		auto enemyController = AddGameObject<EnemyController>();
		SetSharedGameObject(L"EnemyController", enemyController);
		//AddGameObject<Item>();
	}

	// レベルアップイベントの作成
	void GameStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		m_player = AddGameObject<PlayerController>();
		SetSharedGameObject(L"Player", m_player);
		m_player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
	} // end CreatePlayer	

	void GameStage::CreateUI()
	{
		// ExpバーとHpバーの作成
		AddGameObject<HpBar>();
		AddGameObject<ExpBar>();

		// HpとExpの数字表記を作成
		AddGameObject<HpNumber>();
		AddGameObject<ExpNumber>();

		// 残り時間の表示UIを作成
		auto time = AddGameObject<TimeNumber>();
		AddGameObject<TimeChara>();
		SetSharedGameObject(L"Time", time);
	} // end CreateUI


	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			CreatePlayer();
			// 敵の作成
			CreateEnemy();
			// レベルアップイベントの作成
			CreateLevelUpEvent();

			// 地面の作成
			AddGameObject<Field>();

			// テスト用
			AddGameObject<GimmickController>();

			// UIの作成
			CreateUI();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			maincamera->SetTarget(m_player);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}
}
//end basecross
