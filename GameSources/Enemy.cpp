/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const shared_ptr<PlayerController>& player,
		const Vec3& speed,
		const Vec3& position
	) :
		GameObject(stage),
		m_player(player),
		m_speed(speed),
		m_position(position)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::OnCreate()
	{
		m_draw = AddComponent<PNTStaticDraw>();
		m_draw->SetMeshResource(L"DEFAULT_CUBE");
		m_draw->SetOwnShadowActive(true);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);
	}

	void Enemy::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto enemyPos = m_transform->GetPosition();
		auto playerPos = m_player->GetPosition();

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
}