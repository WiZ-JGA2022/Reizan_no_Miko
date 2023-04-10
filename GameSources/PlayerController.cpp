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

		if (m_recastFlame <= 0)
		{
			GetStage()->AddGameObject<PlayerBullet>(GetThis<PlayerController>());
			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}
	}

	void PlayerController::PlayerMoveProcess()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto device = app->GetInputDevice(); 
		auto& pad = device.GetControlerVec()[0];

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);
		Vec3 padRStick(pad.fThumbRX, 0.0f, pad.fThumbRY);

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		// 移動処理
		auto pos = m_transform->GetPosition();
		pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;

		m_transform->SetPosition(pos);

		if (padRStick.length() > 0.0f) 
		{
			float rotY = atan2f(-padRStick.z, padRStick.x); 
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // 回転処理
		}
	}
}
