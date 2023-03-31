/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_speed(1.0f),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_speed(1.0f),
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
			// 処理を停止し、見えなくする
			//SetUpdateActive(false);
			//SetDrawActive(false);
			return;
		}

	} // end OnCollisionEnter

	void Enemy::MoveEnemy()
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得

		m_direction = playerPos - pos; // プレイヤーへの方向を計算

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +	
			m_direction.y * m_direction.y + 
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// ここまで

		pos += m_direction * m_speed * delta;	// 移動の計算
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Enemy::SetPosition(const Vec3& Emitter)
	{
		//m_transform->ResetPosition(Emitter);
		GetStage()->RemoveGameObject<Enemy>(NULL);

		SetUpdateActive(true);
		SetDrawActive(true);
	}
}