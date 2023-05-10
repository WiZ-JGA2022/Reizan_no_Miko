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

		//auto pos = GetStage()->AddGameObject<EnemyController>()->SetPos();
		m_position = m_points[0];

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

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


		//敵の移動の順番
		if (m_currentPointIndex == 0)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 20.0f));
		}
		else if (m_currentPointIndex == 1)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 20.0f));
			//MoveEnemy();
		}
		else if(m_currentPointIndex >= 2)
		{
			//MoveEnemyPlayer();
			MoveEnemyKeyStone();
		}
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

	void SimpleEnemy::MoveEnemy()//シンプル
	{
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

	void SimpleEnemy::MoveEnemyPoint(Vec3 point)//チェックポイントに向かって
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto pointPos = point;

		Vec3 positionControl(0.0f, 0.0f, 0.0f);
		m_directionPoint = pointPos + positionControl - pos; // プレイヤーへの方向を計算

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_directionPoint.x * m_directionPoint.x +
			m_directionPoint.y * m_directionPoint.y +
			m_directionPoint.z * m_directionPoint.z);
		m_directionPoint *= normalizeMagnification;
		// ここまで

		pos += m_directionPoint * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_directionPoint.z, m_directionPoint.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理

		for (int i = 0; i < 1; i++)
		{
			if (m_currentPointIndex == 0)
			{
				if (point.z >= pos.z)
				{
					m_currentPointIndex++;
					break;
				}
			}
			if (m_currentPointIndex == 1)
			{
				if (point.x >= pos.x)
				{
					m_currentPointIndex++;
					break;
				}
			}
			
		}
	}


	void SimpleEnemy::MoveEnemyPlayer()//プレイヤーに向かって
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得
		auto playerScale = playerTrans->GetScale();

		Vec3 positionControl(0.0f, playerScale.y, 0.0f);
		m_directionPlayer = playerPos + positionControl - pos; // プレイヤーへの方向を計算

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_directionPlayer.x * m_directionPlayer.x +
			m_directionPlayer.y * m_directionPlayer.y +
			m_directionPlayer.z * m_directionPlayer.z);
		m_directionPlayer *= normalizeMagnification;
		// ここまで

		pos += m_directionPlayer * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_directionPlayer.z, m_directionPlayer.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void SimpleEnemy::MoveEnemyKeyStone()//要石に向かって
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto stoneTrans = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone")->GetComponent<Transform>();
		auto stonePos = stoneTrans->GetPosition(); // 要石の位置ベクトルを取得

		auto stoneScale = stoneTrans->GetScale();// 要石のスケールを取得
		Vec3 positionControl(0.0f, stoneScale.y, 0.0f);//要石の位置調整
		Vec3 stonePosition = stonePos + (positionControl / 2);
		m_directionKeyStone = stonePosition - pos; // 要石への方向を計算

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_directionKeyStone.x * m_directionKeyStone.x +
			m_directionKeyStone.y * m_directionKeyStone.y +
			m_directionKeyStone.z * m_directionKeyStone.z);
		m_directionKeyStone *= normalizeMagnification;
		// ここまで

		pos += m_directionKeyStone * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_directionKeyStone.z, m_directionKeyStone.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
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