/*!
@file PlayerController.cpp
@brief プレイヤーキャラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class PlayerController : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築と破棄

	void PlayerController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(0.0f, 0.0f, 0.0f);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		// 衝突判定はAuto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(false);

		// 影をつける
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		// Playerオブジェクトの初期設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
	}

	void PlayerController::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		levelUpEvent->LevelUpEvent();
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		if (playerStatus->GetStatusValue(L"HP") <= 0)
		{
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		
		m_recastFlame -= 0.1f;

		// Playerの移動処理
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime(); // 前フレームからの経過時間（60FPS）

		// ゲームパッドを使用する
		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		if (padLStick.length() > 0.0f)
		{
			float stickRad = atan2(padLStick.z, padLStick.x);

			// カメラの回り込みを取得
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
			if (mainCamera)
			{
				float cameraAngle = mainCamera->GetAngle();

				stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}
		}

		// 移動処理
		auto pos = m_transform->GetPosition();
		pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;

		m_transform->SetPosition(pos);

		if (padLStick.length() > 0.0f) // スティックの入力確認
		{
			// スティックの傾きに合わせてオブジェクトを回転させる
			float rotY = atan2f(-padLStick.z, padLStick.x); // 2次元ベクトルを角度(ラジアン)に変換する
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // Y軸中心の回転（キャラクターをゼロ度方向に向かせるために90度多く回転させる）
		}

		if (m_recastFlame <= 0)
		{
			GetStage()->AddGameObject<PlayerBullet>(GetThis<PlayerController>());
			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}
	}

	void PlayerController::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		if (other->FindTag(L"Enemy"))
		{
			playerStatus->PlayerDamageProcess();
			return;
		}

	}
}
