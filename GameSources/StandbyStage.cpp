/*!
@file StandbyStage.cpp
@brief 準備フェーズステージの実装
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
			AddGameObject<StageCollision>(Vec3(30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -16.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-16.0f, 1.0f, 7.5f), Vec3(28.0f, 3.0f, 8.5f));
			AddGameObject<StageCollision>(Vec3(14.5f, 1.0f, 26.0f), Vec3(31.5f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(7.5f, 1.0f, 53.0f), Vec3(3.0f, 3.0f, 18.0f));
			AddGameObject<StageCollision>(Vec3(-8.0f, 1.0f, 52.0f), Vec3(3.0f, 3.0f, 16.5f));

			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);

			AddGameObject<KeyStoneGauge>(stone);

			// UIの作成
			CreateUI();
			AddGameObject<FadeIn>(L"FADE_WHITE");
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToFirstStage");
		}
	}

	// デバッグ文字列表示用
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

}