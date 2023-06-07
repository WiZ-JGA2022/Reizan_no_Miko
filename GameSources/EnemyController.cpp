/*!
@file EnemyController.cpp
@brief “G‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyController::EnemyController(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_RandomRange(5),
		m_Distance(5),
		m_DelayCount(600),
		m_delayFlame(0),
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
		if (!player->GetDrawActive() || player->GetCondition() == 0)
		{
			return;
		}
		m_delayFlame--;

		auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();

		if (m_delayFlame <= 0)
		{
			GetStage()->AddGameObject<EnemySpawn>()->Spawn2(Vec3(20.0f, 1.5f, 60.0f));
			
			//GetStage()->AddGameObject<EnemySpawn>();

			//auto enemy = GetStage()->AddGameObject<Oni>(Vec3(20.0f, 0.0f, 40.0f));
			//GetStage()->AddGameObject<EnemyBullet>();
			//GetStage()->AddGameObject<EnemyBullet>(enemy);
			m_delayFlame = m_DelayCount;
		}
	}
}
//end basecross
