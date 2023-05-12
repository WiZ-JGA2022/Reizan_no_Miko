/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StandbyStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, 10.0f);
		const Vec3 at(0.0f, 1.0f, 0.0f);

		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	// レベルアップイベントの作成
	void StandbyStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//プレイヤーの作成
	void StandbyStage::CreatePlayer() {
		m_player = AddGameObject<PlayerController>(0);
		SetSharedGameObject(L"Player", m_player);
		m_player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
	} // end CreatePlayer	

	void StandbyStage::CreateUI()
	{
		// ExpバーとHpバーの作成
		AddGameObject<HpBar>();
		AddGameObject<ExpBar>();

		// HpとExpの数字表記を作成
		AddGameObject<HpNumber>();
		AddGameObject<ExpNumber>();

		// 残り時間の表示UIを作成
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false);
		SetSharedGameObject(L"Time", time);

		AddGameObject<TimeChara>();

		AddGameObject<TrapSelect>();

		AddGameObject<ButtonSelect>();

		AddGameObject<StandbySprite>();

		AddGameObject<TrapNumber>();

		AddGameObject<TutorialUI>();
	} // end CreateUI


	void StandbyStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void StandbyStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void StandbyStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateLevelUpEvent();
			//プレーヤーの作成
			CreatePlayer();

			// 地面の作成

			AddGameObject<Field>();
			AddGameObject<StageCollision>(Vec3(29.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision2>(Vec3(-30.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision3>(Vec3(0.0f, 4.5f, -15.0f));
			AddGameObject<StageCollision4>(Vec3(-17.5f, 1.0f, 12.5f));
			AddGameObject<StageCollision5>(Vec3(13.5f, 1.0f, 28.0f));
			AddGameObject<StageCollision6>(Vec3(13.0f, 1.0f, 58.0f));
			AddGameObject<StageCollision7>(Vec3(-13.5f, 1.0f, 57.5f));

			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);
			
			AddGameObject<KeyStoneGauge>(stone);

			

			auto blockingStone = AddGameObject<BlockingStone>();
			SetSharedGameObject(L"BlockingStone", blockingStone);

			// UIの作成
			CreateUI();
			PlayBGM();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
			maincamera->SetTargetObject(m_player);
		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {
		auto scene = App::GetApp()->GetScene<Scene>();
		auto camera = GetView()->GetTargetCamera();
		auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		if (time->GetTimeLeft() <= 0.0f)
		{
			scene->SetBeforePlayerPosition(m_player->GetComponent<Transform>()->GetPosition());
			scene->SetBeforePlayerQuaternion(m_player->GetComponent<Transform>()->GetQuaternion());
			scene->SetBeforeCameraRadXZ(maincamera->GetRadXZ());
			scene->SetBeforeCameraRadY(maincamera->GetRadY());
			scene->SetBeforeCameraAngle(maincamera->GetAngle());
			scene->SetBeforeCameraAt(maincamera->GetAt());
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");
		}
	}

	// デバッグ文字列表示用
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw(); 
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		
		auto scene = App::GetApp()->GetScene<Scene>();

		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetAt(scene->GetBeforeCameraAt());
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
	}

	// レベルアップイベントの作成
	void GameStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		Vec3 beforePlayerPosition = App::GetApp()->GetScene<Scene>()->GetBeforePlayerPosition();
		Quat beforePlayerQuaternion = App::GetApp()->GetScene<Scene>()->GetBeforePlayerQuaternion();
		m_player = AddGameObject<PlayerController>(beforePlayerPosition, beforePlayerQuaternion, 1);
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
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false);
		SetSharedGameObject(L"Time", time);
		
		AddGameObject<TimeChara>();

		AddGameObject<GameSprite>();
	} // end CreateUI

	void GameStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

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
			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);
			AddGameObject<StageCollision>(Vec3(29.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision2>(Vec3(-30.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision3>(Vec3(0.0f, 4.5f, -15.0f));
			AddGameObject<StageCollision4>(Vec3(-17.5f, 1.0f, 12.5f));
			AddGameObject<StageCollision5>(Vec3(13.5f, 1.0f, 28.0f));
			AddGameObject<StageCollision6>(Vec3(13.0f, 1.0f, 58.0f));
			AddGameObject<StageCollision7>(Vec3(-13.5f, 1.0f, 57.5f));

			AddGameObject<KeyStoneGauge>(stone);

			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			for (int i = 0; i < scene->GetBeforePlacedTrap(0); i++)
			{
				AddGameObject<SpikeTrap>(scene->GetBeforeSpikePosition(i), Vec3(5.0f, 0.5f, 5.0f));
			}
			for (int i = 0; i < scene->GetBeforePlacedTrap(1); i++)
			{
				AddGameObject<SpurtLava>(scene->GetBeforeLavaPosition(i), Vec3(4.0f, 20.0f, 4.0f));
			}

			// UIの作成
			CreateUI();
			PlayBGM();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
			maincamera->SetTargetObject(m_player);
		}
		catch (...) {
			throw;
		}
	}

	//更新
	void GameStage::OnUpdate() {
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		if (!player->GetDrawActive())
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			return;
		}
		if (time->GetTimeLeft() <= 0.0f)
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			return;
		}
	} // end OnUpdate

	void GameStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//スプライトの作成
	void TitleStage::CreateTitleSprite() {
		AddGameObject<TitleSprite>();
		AddGameObject<StartSprite>();
	} // end CreateTitleSprite

	void TitleStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void TitleStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//初期化
	void TitleStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();

		PlayBGM();

	} // end OnCreate

	//更新
	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());

	} // end OnUpdate

	//Bボタン
	void TitleStage::OnPushB() {
		AddGameObject<FadeIn>();

		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"SELECT_SE", 0, 0.5f);
		PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");

	} // end OnPushB


	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//スプライトの作成
	void ResultStage::CreateResultSprite() {
		AddGameObject<ResultSprite>();
	} // end CreateResultSprite

	void ResultStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GAMEOVER_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void ResultStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//初期化
	void ResultStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateResultSprite();
		PlayBGM();
	} // end OnCreate

	//更新
	void ResultStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<ResultStage>());

	} // end OnUpdate

	//Bボタン
	void ResultStage::OnPushB() {
		AddGameObject<FadeOut>();

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB

	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//スプライトの作成
	void ClearStage::CreateResultSprite() {
		AddGameObject<ClearSprite>();
	} // end CreateResultSprite

	void ClearStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GAMECLEAR_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void ClearStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//初期化
	void ClearStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateResultSprite();
		PlayBGM();
	} // end OnCreate

	//更新
	void ClearStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<ClearStage>());

	} // end OnUpdate

	//Bボタン
	void ClearStage::OnPushB() {
		AddGameObject<FadeOut>();

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB

}
//end basecross
