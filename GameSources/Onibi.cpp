/*!
@file Oni.cpp
@brief 単純な動きの敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Onibi::Onibi(const shared_ptr<Stage>& stage) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(Vec3 (2,2,2)),
		m_scale(Vec3(3.0f))
	{
	}
	Onibi::~Onibi() {}

	void Onibi::OnCreate()
	{
		Enemy::CreateEnemyMesh(m_position, m_scale, L"ONI_WALK", L"walk");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);

	}

	void Onibi::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// レベルアップイベント実行中またはプレイヤーが居ないとき
		if (levelUpEvent->GetEventActive() || !player->GetDrawActive())
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
		m_damageDelayFlame--;

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);

		Onibi::MoveEnemyPlayer();
	}

	void Onibi::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// 弾にあたったら
		if (other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.1f);

			// ダメージを受ける(ダメージ量はプレイヤーの攻撃力依存)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}

		// 罠にあたったら
		if (other->FindTag(L"SpikeTrap"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"SPIKEDAMAGE_SE", 0, 0.3f);

			// ダメージを受ける(ダメージ量はプレイヤーの攻撃力依存)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}

		// 溶岩にあたったら
		if (other->FindTag(L"SpurtLava"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"SPIKEDAMAGE_SE", 0, 0.3f);

			// ダメージを受ける(ダメージ量はプレイヤーの攻撃力依存)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}
	} // end OnCollisionEnter

	void Onibi::OnCollisionExcute(shared_ptr<GameObject>& other)
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

		if (other->FindTag(L"KeyStone"))
		{
			auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
			Enemy::ChangeEnemyAnimation(L"ONI_ATTACK", L"attack");
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;

				return;
			}
		}
	} // end OnCollisionEnter

	void Onibi::MoveEnemyPlayer()//チェックポイントに向かって
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		Vec3 pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得
		playerPos.y + 5;

		m_directionPoint = playerPos - pos; // プレイヤーへの方向を計算
		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_directionPlayer.x * m_directionPlayer.x +
			m_directionPlayer.y * m_directionPlayer.y +
			m_directionPlayer.z * m_directionPlayer.z);
		m_directionPlayer *= normalizeMagnification;

		pos += m_directionPoint * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_directionPoint.z, m_directionPoint.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Onibi::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float Onibi::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}