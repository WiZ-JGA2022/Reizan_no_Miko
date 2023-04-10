/*!
@file Item.cpp
@brief アイテムの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Item::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		auto ItemColl = AddComponent<CollisionObb>();
		ItemColl->SetAfterCollision(AfterCollision::None);

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		MoveExp();
	}

	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
			playerStatus->ExpValueUpdate(m_expValue);
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
	}

	void Item::MoveExp()
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得

		m_direction = playerPos - pos; // プレイヤーとの距離を計算

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		m_pickupRange = playerStatus->GetStatusValue(L"PICKUP");

		// プレイヤーの取得範囲内にいなければ
		if (m_direction.length() > m_pickupRange)
		{
			// 動かない
			return;
		}

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +
			m_direction.y * m_direction.y +
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// ここまで

		pos += m_direction * m_speed * delta;	// 移動の計算
		float rotationY = atan2f(-m_direction.z, m_direction.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理

	}
}
//end basecross
