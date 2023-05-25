/*!
@file Onibi.cpp
@brief 単純な動きの敵
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Onibi::Onibi(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(position),
		m_scale(Vec3(3.0f))
	{
	}
	Onibi::~Onibi() {}

	void Onibi::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		
		AddTag(L"Enemy");

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring normalEffectStr = DataDir + L"Effects\\" + L"fire04.efk";
		wstring damageEffectStr = DataDir + L"Effects\\" + L"damage.efk";
		wstring diedEffectStr = DataDir + L"Effects\\" + L"soul.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_normalEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, normalEffectStr);
		m_damageEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, damageEffectStr);
		m_diedEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, diedEffectStr);
		//エフェクトのプレイ
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_normalEffect, m_transform->GetPosition(), Vec3(0.5f));
	}

	void Onibi::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// レベルアップイベント実行中またはプレイヤーが居ないとき
		if (!player->GetDrawActive())
		{
			//m_EfkPlay2->StopEffect();
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
		MoveEnemyPlayer();
	}

	void Onibi::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// 弾にあたったら
		if (other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.3f);

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
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;

				return;
			}
		}
	} // end OnCollisionEnter

	void Onibi::MoveEnemyPlayer()
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		Vec3 pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得
		playerPos.y + 5;

		m_direction = playerPos - pos; // プレイヤーへの方向を計算
		m_direction.normalize(); // 正規化

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_direction.z, m_direction.x); // 回転の計算

		m_EfkPlay->AddLocation(m_direction * m_statusValue[L"SPD"] * delta); // エフェクトの移動
		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Onibi::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));
		m_EfkPlay2 = ObjectFactory::Create<EfkPlay>(m_damageEffect, m_transform->GetPosition(), Vec3(0.5f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float Onibi::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}