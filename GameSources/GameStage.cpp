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
	}

	// レベルアップイベントの作成
	void GameStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		m_player = AddGameObject<PlayerController>(1);
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
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds);
		AddGameObject<TimeChara>();

		AddGameObject<GameSprite>();

		SetSharedGameObject(L"Time", time);
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
			AddGameObject<Field2>(Vec3(10.0f, 3.5f, 10.0f));
			AddGameObject<Field2>(Vec3(-10.0f, 3.5f, 30.0f));
			//AddGameObject<SpurtLava>(Vec3(0), Vec3(5.0f, 5.0f, 5.0f));

			// ギミックの作成
			//auto gimmick = AddGameObject<GimmickController>();
			//SetSharedGameObject(L"GimmickController", gimmick);

			// UIの作成
			CreateUI();
			PlayBGM();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			maincamera->SetTarget(m_player);
		}
		catch (...) {
			throw;
		}
	}

	//更新
	void GameStage::OnUpdate() {
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		if (!player->GetDrawActive())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
		}
	} // end OnUpdate

	void GameStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	//--------------------------------------------------------------------------------------
	//	スタンバイステージクラス実体
	//--------------------------------------------------------------------------------------
	void StandbyStage::CreateViewLight() {
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
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds);
		AddGameObject<TimeChara>();

		m_trap = AddGameObject<TrapSprite>();

		AddGameObject<StandbySprite>();
		SetSharedGameObject(L"Time", time);
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
			AddGameObject<Field2>(Vec3(10.0f, 3.5f, 10.0f));
			AddGameObject<Field2>(Vec3(-10.0f, 3.5f, 30.0f));
			//AddGameObject<SpurtLava>(Vec3(0), Vec3(5.0f, 5.0f, 5.0f));

			// ギミックの作成
			//auto gimmick = AddGameObject<GimmickController>();
			//SetSharedGameObject(L"GimmickController", gimmick);

			// UIの作成
			CreateUI();
			PlayBGM();

			// メインカメラにプレイヤーをセットする
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			maincamera->SetTarget(m_player);
		}
		catch (...) {
			throw;
		}
	}

	//更新
	void StandbyStage::OnUpdate() {
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		if (time->GetTimeLeft() <= 0.0f)
		{

			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	} // end OnUpdate

	void StandbyStage::OnDraw()
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
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");

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
		m_BGM = XAPtr->Start(L"GAMECLEAR_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
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
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB
}
//end basecross
