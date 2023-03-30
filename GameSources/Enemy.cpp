/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_currentPointIndex(0),
		m_speed(1.0f),
		m_position(position),
		m_start(0),
		m_end(0)
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
		ptrColl->SetAfterCollision(AfterCollision::None);
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

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// 弾にあたったら(テスト用でplayer)
		if (Other->FindTag(L"Player"))
		{
			m_position = m_transform->GetPosition();
			// 処理を停止し、見えなくする
			SetUpdateActive(false);
			SetDrawActive(false);
			return;
		}

	} // end OnCollisionEnter

	void Enemy::MoveEnemy()
	{
		auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();

		// 線形補間の始点と終点を設定
		m_points = {
			m_position,
			playerPos
		};

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		static float a = 0.0f; // 0 ～ 1の係数(0 - 100%)

		m_start = m_points[m_currentPointIndex % m_points.size()];
		m_end = m_points[(m_currentPointIndex + 1) % m_points.size()];
		Vec3 pos = Utility::Lerp(m_start, m_end, a); 
		a += m_speed * delta / (m_end - m_start).length(); 
		if (a >= 1.0f)
		{
			m_currentPointIndex++;
			a = 0.0f;
		}

		m_transform->SetPosition(pos); // 座標の更新

		//auto enemyPos = m_transform->GetPosition();
		//auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		//auto playerTrans = playerObj->GetComponent<Transform>();
		//auto playerPos = playerTrans->GetPosition();

		//if (playerPos.x == enemyPos.x) { m_speed.x = 0; }
		//if (playerPos.x < enemyPos.x) { m_speed.x = -1; }
		//if (playerPos.x > enemyPos.x) { m_speed.x = +1; }

		//if (playerPos.z == enemyPos.z) { m_speed.z = 0; }
		//if (playerPos.z < enemyPos.z) { m_speed.z = -1; }
		//if (playerPos.z > enemyPos.z) { m_speed.z = +1; }


		//float rotationY = atan2f(playerPos.z, playerPos.x);
		//float enemyMoveX = enemyPos.x + m_speed.x * delta;
		//float enemyMoveZ = enemyPos.z + m_speed.z * delta;
		//m_transform->SetRotation(Vec3(0, rotationY + XM_PIDIV2, 0));
		//m_transform->SetPosition(enemyMoveX, enemyPos.y, enemyMoveZ);

	}

	void Enemy::SetPosition(const Vec3& Emitter)
	{
		//m_transform->ResetPosition(Emitter);
		GetStage()->RemoveGameObject<Enemy>(NULL);

		SetUpdateActive(true);
		SetDrawActive(true);
	}
}