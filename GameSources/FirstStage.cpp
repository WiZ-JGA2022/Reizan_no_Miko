/*!
@file FirstStage.cpp
@brief ゲームステージ実体
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void FirstStage::CreateViewLight() {
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
	void FirstStage::CreateEnemy() {
		CreateSharedObjectGroup(L"EnemyGroup");
		auto enemyController = AddGameObject<EnemyController>();
		SetSharedGameObject(L"EnemyController", enemyController);
	}


	//プレイヤーの作成
	void FirstStage::CreatePlayer() {
		// スタンバイステージ終了時の情報を取得
		Vec3 beforePlayerPosition = App::GetApp()->GetScene<Scene>()->GetBeforePlayerPosition();
		Quat beforePlayerQuaternion = App::GetApp()->GetScene<Scene>()->GetBeforePlayerQuaternion();

		// 生成時に位置と回転の情報を入力
		auto player = AddGameObject<PlayerController>(beforePlayerPosition, beforePlayerQuaternion, 1);
		SetSharedGameObject(L"Player", player);
		player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_RED");
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_GREEN");
	} // end CreatePlayer	

	void FirstStage::CreateUI()
	{
		// Hpバーの作成
		AddGameObject<HpBar>();

		// Hpの数字表記を作成
		AddGameObject<HpNumber>();

		AddGameObject<StrengthSprite>();

		AddGameObject<RightStick>();

		// 残り時間の表示UIを作成
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false,false);
		SetSharedGameObject(L"Time", time);
		
		AddGameObject<TimeChara>();

		AddGameObject<GameSprite>();
	} // end CreateUI

	void FirstStage::PlayBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_bgm = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}

	void FirstStage::OnDestroy()
	{
		//BGMのストップ
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void FirstStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			CreatePlayer();
			// 敵の作成
			CreateEnemy();

			// 地面の作成
			AddGameObject<Field>();
			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);
			AddGameObject<StageCollision>(Vec3(30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -16.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-16.0f, 1.0f, 7.5f), Vec3(28.0f, 3.0f, 8.5f));
			AddGameObject<StageCollision>(Vec3(14.5f, 1.0f, 26.0f), Vec3(31.5f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(7.5f, 1.0f, 53.0f), Vec3(3.0f, 3.0f, 18.0f));
			AddGameObject<StageCollision>(Vec3(-8.0f, 1.0f, 52.0f), Vec3(3.0f, 3.0f, 16.5f));

			// シーンの取得
			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			// スタンバイステージで罠が設置されている時のみループする
			for (int i = 0; i < scene->GetBeforePlacedTrap(0); i++)
			{
				// 棘罠の生成
				AddGameObject<SpikeTrap>(scene->GetBeforeSpikePosition(i), Vec3(5.0f, 0.5f, 5.0f));
			}
			for (int i = 0; i < scene->GetBeforePlacedTrap(1); i++)
			{
				// 溶岩罠の生成
				AddGameObject<SpurtLava>(scene->GetBeforeLavaPosition(i), Vec3(4.0f, 20.0f, 4.0f));
			}

			// UIの作成
			CreateUI();
			PlayBGM();

			// プレイヤーとカメラを取得
			auto player = GetSharedGameObject<PlayerController>(L"Player");
			auto& camera = GetView()->GetTargetCamera();
			auto myCamera = dynamic_pointer_cast<MyCamera>(camera);
			// メインカメラのターゲットにプレイヤーをセットする
			myCamera->SetTargetObject(player);
		}
		catch (...) {
			throw;
		}
	}

	//更新
	void FirstStage::OnUpdate() {
		// 各種情報の取得
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto& device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		// リセットコマンドが押されたら
		if (pad.wButtons & XINPUT_GAMEPAD_START && pad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			// ステージ変更フラグをオン
			m_isChangeStage = true;
			// タイトルに戻る
			PostEvent(0.1f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
		}

		// プレイヤーが描画されなくなったら
		if (!player->GetDrawActive())
		{
			// ステージ変更フラグをオン
			m_isChangeStage = true;
			// Defeatステージに移動
			AddGameObject<FadeOut>(L"FADE_BLACK");
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDefeatStage");
			return;
		}
		// 時間切れになったら
		if (time->GetTimeLeft() <= 0.0f)
		{
			// ステージ変更フラグをオン
			m_isChangeStage = true;
			// Clearステージに移動
			AddGameObject<FadeOut>(L"FADE_WHITE");
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			return;
		}
	} // end OnUpdate
}
//end basecross
