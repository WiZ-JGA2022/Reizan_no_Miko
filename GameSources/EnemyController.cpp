/*!
@file EnemyController.cpp
@brief �G�Ȃǎ���
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
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}
		m_delayFlame--;

		auto playerObj = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();

		//�G�̈ʒu�̕��������肷��(+,-���W������)
		int rnd_x = rand() % 2;
		int rnd_z = rand() % 2;
		if (rnd_x > 0) { m_sign_x = 1; } else { m_sign_x = -1; }
		if (rnd_z > 0) { m_sign_z = 1; } else { m_sign_z = -1; }

		// ���̃I�u�W�F�N�g�̈ʒu����Ƃ��������_���ȏꏊ�ɏo��������
		m_enemyPos = Vec3(
			(playerPos.x + m_Distance + rand() % m_RandomRange) * m_sign_x,
			m_position.y, 
			(playerPos.z + m_Distance + rand() % m_RandomRange) * m_sign_z
		);


		if (m_delayFlame <= 0)
		{
			GetStage()->AddGameObject<Enemy>(m_enemyPos);
			m_enemyNum++;
			//GetStage()->AddGameObject<EnemyBullet>();
			m_delayFlame = m_DelayCount;
		}

		wstringstream wss;
		wss << L"m_enemyNum : " <<
			m_enemyNum << endl;
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());
	}

	int EnemyController::GetEnemyNumber()
	{
		return m_enemyNum;
	}

}
//end basecross
