/*!
@file SimpleEnemy.cpp
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SimpleEnemy::SimpleEnemy(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(position),
		m_currentPointIndex(0)
		{
		}
	SimpleEnemy::~SimpleEnemy() {}

	void SimpleEnemy::OnCreate()
	{

		Enemy::OnCreate();
		
		m_position = m_points[0];

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		int rnd = rand() % 10;
		Vec3 m_randomPosition(0.0f, 0.0f, -rnd);

		float direction_x = m_direction[1].x - m_points[2].x;
		float direction_y = m_direction[1].z - m_points[2].z;

		Vec3 m_randomDirection(-direction_x+20.0f, 0.0f,direction_y);
		//Vec3 m_randomDirection(30, 0.0f,-30);
		
		m_direction[2] = m_randomDirection;
		m_points[3] = m_randomPosition;

	}

	void SimpleEnemy::OnUpdate()
	{
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
			// expを落とす
			//GetStage()->AddGameObject<Item>(m_transform->GetPosition());
			// 処理を停止し、見えなくする
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		m_damageDelayFlame--;
		MoveEnemy();
	}

	void SimpleEnemy::OnCollisionEnter(shared_ptr<GameObject>& other)
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

	void SimpleEnemy::OnCollisionExcute(shared_ptr<GameObject>& other)
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

	void SimpleEnemy::MoveEnemy()
	{

		if (3 < m_currentPointIndex)
		{
			auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;
			}
			m_transform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			return;
		}

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_direction[m_currentPointIndex].x * m_direction[m_currentPointIndex].x +
			m_direction[m_currentPointIndex].y * m_direction[m_currentPointIndex].y +
			m_direction[m_currentPointIndex].z * m_direction[m_currentPointIndex].z);
		m_direction[m_currentPointIndex] *= normalizeMagnification;
		// ここまで

		m_position += m_direction[m_currentPointIndex] * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_direction[m_currentPointIndex].z, m_direction[m_currentPointIndex].x); // 回転の計算

		m_transform->SetRotation(0.0f, rotationY, 0.0f);
		m_transform->SetPosition(m_position);

		for (int i = 0; i < 1; i++)
		{
			if (m_currentPointIndex == 0)
			{
				if ((int)m_position.z == (int)m_points[m_currentPointIndex + 1].z)
				{
					m_currentPointIndex++;
					break;
				}
				break;
			}
			if ((int)m_position.x == (int)m_points[m_currentPointIndex + 1].x)
			{
				m_currentPointIndex++;
				break;
			}
		}
	}

	void SimpleEnemy::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float SimpleEnemy::GetEnemyStatus(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}
}