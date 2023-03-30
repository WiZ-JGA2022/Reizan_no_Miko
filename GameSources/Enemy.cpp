/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_speed(0),
		m_position(position)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		// 衝突判定はAuto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(true);

		// 影をつける
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"WALL_TX");
		drawComp->SetOwnShadowActive(true);


		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());
	}

	void Enemy::OnUpdate()
	{
		MoveEnemy();
	}

	void Enemy::MoveEnemy()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto enemyPos = m_transform->GetPosition();
		auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();

		if (playerPos.x == enemyPos.x) { m_speed.x = 0; }
		if (playerPos.x < enemyPos.x) { m_speed.x = -1; }
		if (playerPos.x > enemyPos.x) { m_speed.x = +1; }

		if (playerPos.z == enemyPos.z) { m_speed.z = 0; }
		if (playerPos.z < enemyPos.z) { m_speed.z = -1; }
		if (playerPos.z > enemyPos.z) { m_speed.z = +1; }


		float rotationY = atan2f(playerPos.z, playerPos.x);
		float enemyMoveX = enemyPos.x + m_speed.x * delta;
		float enemyMoveZ = enemyPos.z + m_speed.z * delta;
		m_transform->SetRotation(Vec3(0, rotationY + XM_PIDIV2, 0));
		m_transform->SetPosition(enemyMoveX, enemyPos.y, enemyMoveZ);

	}

	void Enemy::SetPosition(const Vec3& Emitter)
	{
		m_transform->ResetPosition(Emitter);
	}
}