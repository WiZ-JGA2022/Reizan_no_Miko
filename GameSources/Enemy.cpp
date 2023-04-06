/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
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
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(true);

		// 影をつける
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"WALL_TX");
		drawComp->SetOwnShadowActive(true);

		auto enemyController = GetStage()->GetSharedGameObject<EnemyController>(L"EnemyController");

		AddTag(L"Enemy"/*enemyController->GetEnemyNumber()*/); 
		// 直前に設定された文字のNULL文字以降を指定する数字を+演算子で足すと空判定になる
		// Enemyだと5以降の数字を+で足すと空判定になる?(E:0 n:1 e:2 m:3 y:4 \0:5)

		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		playerStatus->SetEnemyATK(m_statusValue[L"ATK"]);
	}

	void Enemy::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		// レベルアップイベントがONになったら
		if (levelUpEvent->GetControllerSprite())
		{
			// 処理を停止する
			return;
		}

		// HPが0になったら
		if (m_statusValue[L"HP"] <= 0)
		{
			// 処理を停止し、見えなくする
			SetUpdateActive(false);
			SetDrawActive(false);
		}

		MoveEnemy();
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// 弾にあたったら
		if (Other->FindTag(L"PlayerBullet"))
		{
			// ダメージを受ける
			EnemyDamageProcess();
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

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Enemy::EnemyDamageProcess()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float damage = playerStatus->GetStatusValue(L"ATK") - (playerStatus->GetStatusValue(L"ATK") * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= damage;
	}

	float Enemy::GetEnemyStatus(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}
}