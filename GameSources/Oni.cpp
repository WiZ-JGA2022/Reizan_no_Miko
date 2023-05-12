/*!
@file Oni.cpp
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Project.h"


namespace basecross {
	Oni::Oni(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(position),
		m_scale(Vec3(3.0f)),
		m_currentPointIndex(0)
	{
	}
	Oni::~Oni() {}

	void Oni::OnCreate()
	{
		Enemy::CreateEnemyMesh(m_position, m_scale, L"ONI_WALK", L"walk");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

	}

	void Oni::OnUpdate()
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

		//敵の移動の順番
		if (m_currentPointIndex == 0)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 40.0f));
		}
		else if (m_currentPointIndex == 1)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 40.0f));
		}
		else if(m_currentPointIndex == 2)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 20.0f));
		}
		else if(m_currentPointIndex == 3)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 20.0f));
		}
		else if(m_currentPointIndex == 4)
		{
			auto stoneTrans = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone")->GetComponent<Transform>();
			MoveEnemyPoint(Vec3(stoneTrans->GetPosition().x, stoneTrans->GetPosition().y + 1.5f, stoneTrans->GetPosition().z));
		}
	}

	void Oni::OnCollisionEnter(shared_ptr<GameObject>& other)
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

	void Oni::OnCollisionExcute(shared_ptr<GameObject>& other)
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

	void Oni::MoveEnemyPoint(const Vec3& point)//チェックポイントに向かって
	{
		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		Vec3 pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得

		m_directionPoint = point - pos; // プレイヤーへの方向を計算
		if (m_directionPoint.x < 0.1f && m_directionPoint.z < 0.1f && m_directionPoint.x > -0.1f && m_directionPoint.z > -0.1f)
		{
			m_currentPointIndex++;
			return;
		}
		m_directionPoint.normalize();

		pos += m_directionPoint * m_statusValue[L"SPD"] * delta;	// 移動の計算
		float rotationY = atan2f(-m_directionPoint.z, m_directionPoint.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
	}

	void Oni::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float Oni::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}