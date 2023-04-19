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
	void PlayerController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(0.0f, 0.0f, 0.0f);
		m_transform->SetScale(0.2f, 0.2f, 0.2f);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		// 衝突判定はAuto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(false);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"HITOTUME");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"HITOTUME");
		drawComp->SetMeshToTransformMatrix(spanMat);
	}

	void PlayerController::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
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
		
		PlayerMoveProcess();

		if (m_recastFlame <= 0 && m_condition == PlayerCondition::Play)
		{
			GetStage()->AddGameObject<PlayerBullet>(GetThis<PlayerController>());

			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		
		if (pad.wPressedButtons & XINPUT_GAMEPAD_X)
		{
			if (m_condition == PlayerCondition::Standby && m_trapCount < 1)
			{
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"SPIKE_SE", 0, 0.3f);
				GetStage()->AddGameObject<SpikeTrap>(Vec3(m_transform->GetPosition().x, -0.5f, m_transform->GetPosition().z), Vec3(5.0f, 0.5f, 5.0f));
				m_trapCount++;
			}
		}
	}

	void PlayerController::PlayerMoveProcess()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		if (padLStick.length() > 0.0f)
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			//XAPtr->Start(L"PLAYERRUN_SE", 1, 0.1f);

			float stickRad = atan2(padLStick.z, padLStick.x);
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MyCamera>(camera);
			if (mainCamera)
			{
				//float cameraAngle = mainCamera->GetAngle();

				//stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}

			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

			// 移動処理
			auto pos = m_transform->GetPosition();
			pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;

			m_transform->SetPosition(pos);
			float rotY = atan2f(-padLStick.z, padLStick.x);
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // 回転処理
		}
	}
}
