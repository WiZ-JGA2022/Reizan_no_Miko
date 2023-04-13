/*!
@file EnemyController.cpp
@brief 敵など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyController::EnemyController(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_RandomRange(5),
		m_Distance(5),
		m_DelayCount(120),
		m_delayFlame(m_DelayCount),
		m_enemyNum(0),
		m_sign_x(1),
		m_sign_z(1),
		m_position(Vec3(-3.0f, 0.0f, 5.0f))
	{
	}
	EnemyController::~EnemyController() {}

	void EnemyController::OnCreate()
	{
		srand((unsigned int)time(NULL));

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);
	}

	void EnemyController::OnUpdate()
	{	
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive() || !player->GetDrawActive())
		{
			return;
		}
		m_delayFlame--;

		auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();

		//敵の位置の符号を決定する(+,-座標を決定)
		int rnd_x = rand() % 2;
		int rnd_z = rand() % 2;
		if (rnd_x > 0) { m_sign_x = 1; } else { m_sign_x = -1; }
		if (rnd_z > 0) { m_sign_z = 1; } else { m_sign_z = -1; }

		// このオブジェクトの位置を基準としたランダムな場所に出現させる
		//m_enemyPos = Vec3(
		//	(playerPos.x + m_Distance + rand() % m_RandomRange) * m_sign_x,
		//	m_position.y, 
		//	(playerPos.z + m_Distance + rand() % m_RandomRange) * m_sign_z
		//);


		if (m_delayFlame <= 0)
		{
			auto enemy = GetStage()->AddGameObject<SimpleEnemy>(Vec3(20.0f, 0.0f, 40.0f));
			//GetStage()->AddGameObject<EnemyBullet>();
			//GetStage()->AddGameObject<EnemyBullet>(enemy);
			m_delayFlame = m_DelayCount;
		}
	}

	int EnemyController::GetEnemyNumber()
	{
		return m_enemyNum;
	}

}
//end basecross
