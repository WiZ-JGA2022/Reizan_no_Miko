/*!
@file Enemy.cpp
@brief 敵全体の親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_ShotRecastCount(300),
		m_shotRecastFlame(m_ShotRecastCount),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_ShotRecastCount(300),
		m_shotRecastFlame(m_ShotRecastCount),
		m_position(position)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::OnCreate()
	{
	}

	void Enemy::OnUpdate()
	{
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// 弾にあたったら
		if (Other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.1f);

			// ダメージを受ける
			EnemyDamageProcess();
			return;
		}

	} // end OnCollisionEnter

	void Enemy::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// プレイヤーにあたったら
		if (other->FindTag(L"Player"))
		{
			if (m_damageDelayFlame <= 0)
			{
				// ダメージを与える
				playerStatus->PlayerDamageProcess(m_statusValue[L"ATK"]);
				m_damageDelayFlame = m_DamageDelayCount;
				return;
			}
		}

	} // end OnCollisionEnter

	void Enemy::CreateEnemyMesh(const Vec3& position, const Vec3& scale, const wstring& meshKey)
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(position);
		m_transform->SetScale(scale);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionCapsule>();
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(true);

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
		ptrShadow->SetMeshResource(meshKey);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(meshKey);
		drawComp->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Enemy");

		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());
		// 透明処理
		SetAlphaActive(true);

		// 描画順の変更
		SetDrawLayer((int)DrawLayer::Bottom);
	}

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
		m_direction.normalize();

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_direction.z, m_direction.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Enemy::ShotBullet()
	{
		GetStage()->AddGameObject<EnemyBullet>(m_transform->GetPosition(), m_statusValue[L"ATK"]);
	}

	void Enemy::EnemyDamageProcess()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float damage = playerStatus->GetStatusValue(L"ATK") - (playerStatus->GetStatusValue(L"ATK") * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= damage;
	}

	float Enemy::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}