/*!
@file StandbyStage.cpp
@brief 準備フェーズステージの実装
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StandbyStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}


	//プレイヤーの作成
	void StandbyStage::CreatePlayer() {
		auto player = AddGameObject<PlayerController>(0);
		SetSharedGameObject(L"Player", player);
		player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_RED");
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_GREEN");
	} // end CreatePlayer	

	void StandbyStage::CreateUI()
	{
		// Hpバーの作成
		AddGameObject<HpBar>();

		// Hpの数字表記を作成
		AddGameObject<HpNumber>();

		AddGameObject<StrengthSprite>();

		// 残り時間の表示UIを作成
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false,true);
		SetSharedGameObject(L"Time", time);

		AddGameObject<TimeChara>();

		AddGameObject<TrapSelect>();

		AddGameObject<ButtonSelect>();

		AddGameObject<StandbySprite>();

		AddGameObject<TrapNumber>();

		AddGameObject<TutorialUI>();

		AddGameObject<RBButtonSprite>();
		AddGameObject<HoldBar>();
	} // end CreateUI


	void StandbyStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_bgm = XAPtr->Start(L"STANDBY_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void StandbyStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void StandbyStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//プレーヤーの作成
			CreatePlayer();

			// 地面の作成
			AddGameObject<Field>();
			AddGameObject<StageCollision>(Vec3(30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -16.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-16.0f, 1.0f, 7.5f), Vec3(28.0f, 3.0f, 8.5f));
			AddGameObject<StageCollision>(Vec3(14.5f, 1.0f, 26.0f), Vec3(31.5f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(7.5f, 1.0f, 53.0f), Vec3(3.0f, 3.0f, 18.0f));
			AddGameObject<StageCollision>(Vec3(-8.0f, 1.0f, 52.0f), Vec3(3.0f, 3.0f, 16.5f));

			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);

			// UIの作成
			CreateUI();
			AddGameObject<FadeIn>(L"FADE_WHITE");
			PlayBGM();

			// メインカメラにプレイヤーをセットする
			auto player = GetSharedGameObject<PlayerController>(L"Player");
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
			maincamera->SetTargetObject(player);
		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {

		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		// リセットコマンド
		if (pad.wButtons & XINPUT_GAMEPAD_START && pad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			m_isChangeStage = true;
			// タイトルに戻る
			PostEvent(0.1f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
		}

		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		if (time->GetTimeLeft() <= 0.0f)
		{
			ChangeStage();
		}
	}

	// デバッグ文字列表示用
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	void StandbyStage::ChangeStage()
	{
		m_isChangeStage = true;

		// 各種情報をシーンに設定
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto camera = GetView()->GetTargetCamera();
		auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
		scene->SetBeforePlayerPosition(player->GetComponent<Transform>()->GetPosition());
		scene->SetBeforePlayerQuaternion(player->GetComponent<Transform>()->GetQuaternion());
		scene->SetBeforeCameraRadXZ(maincamera->GetRadXZ());
		scene->SetBeforeCameraRadY(maincamera->GetRadY());
		scene->SetBeforeCameraAngle(maincamera->GetAngle());
		scene->SetBeforeCameraAt(maincamera->GetAt());

		// ゲームステージへ移動
		PostEvent(0.01f, GetThis<ObjectInterface>(), scene, L"ToFirstStage");
	}
}