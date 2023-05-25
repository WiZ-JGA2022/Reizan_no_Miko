/*!
@file EnemySpawn.cpp
@brief 敵の出現パターンなど
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void EnemySpawn::OnCreate()
	{
		//Spawn1(Vec3(20.0f, 0.0f, 40.0f));
		//Spawn2(Vec3(20.0f, 0.0f, 40.0f));
		//Spawn3(Vec3(20.0f, 0.0f, 40.0f));
		//Spawn4(Vec3(20.0f, 0.0f, 40.0f));
		//Spawn5(Vec3(20.0f, 0.0f, 40.0f));
	}

	void EnemySpawn::OnUpdate()
	{

	}

	void EnemySpawn::Spawn1(Vec3 pos)
	{
		EnemyCreate(pos);
	}

	void EnemySpawn::Spawn2(Vec3 pos)
	{
		// m_enemyInterval = GetStage()->GetSharedGameObject<Enemy>(L"Enemy")->GetComponent<Transform>()->GetScale();

		for (int i = 0;i < 2;i++)
		{
			Vec3 transPos;
			if (i == 0) { transPos = (Vec3(pos.x, pos.y, pos.z + (m_enemyInterval.z * 2))); }
			if (i == 1) { transPos = (Vec3(pos.x, pos.y, pos.z - (m_enemyInterval.z * 2))); }

			EnemyCreate(transPos);
		}
	}

	void EnemySpawn::Spawn3(Vec3 pos)
	{
		for (int i = 0;i < 3;i++)
		{
			Vec3 transPos;
			if (i == 0) { transPos = (Vec3(pos.x + (m_enemyInterval.x * 2), pos.y, pos.z)); }
			if (i == 1) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z + (m_enemyInterval.z * 2))); }
			if (i == 2) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z - (m_enemyInterval.z * 2))); }

			EnemyCreate(transPos);
		}
	}

	void EnemySpawn::Spawn4(Vec3 pos)
	{
		for (int i = 0;i < 4;i++)
		{
			Vec3 transPos;
			if (i == 0) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 1) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }
			if (i == 2) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 3) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }

			EnemyCreate(transPos);
		}
	}

	void EnemySpawn::Spawn5(Vec3 pos)
	{
		for (int i = 0;i < 5;i++)
		{
			Vec3 transPos;
			if (i == 0) { transPos = (Vec3(pos.x + (m_enemyInterval.x * 2), pos.y, pos.z )); }
			if (i == 1) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 2) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }
			if (i == 3) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 4) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }

			EnemyCreate(transPos);
		}
	}

	void EnemySpawn::Spawn6(Vec3 pos)
	{
		for (int i = 0;i < 6;i++)
		{
			Vec3 transPos;
			if (i == 0) { transPos = (Vec3(pos.x + (m_enemyInterval.x * 2), pos.y, pos.z)); }
			if (i == 1) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 2) { transPos = (Vec3(pos.x + m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }
			if (i == 3) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z + m_enemyInterval.z)); }
			if (i == 4) { transPos = (Vec3(pos.x - m_enemyInterval.x, pos.y, pos.z - m_enemyInterval.z)); }
			if (i == 5) { transPos = (Vec3(pos.x - (m_enemyInterval.x * 2), pos.y, pos.z)); }

			EnemyCreate(transPos);
		}
	}

	void EnemySpawn::EnemyCreate(Vec3 transPos)
	{
		auto enemy = GetStage()->AddGameObject<Oni>(transPos);
		//auto enemy2 = GetStage->AddGameObject<Onibi>(transPos);
		//GetStage()->AddGameObject<EnemyBullet>();
		GetStage()->AddGameObject<EnemyBullet>(transPos,2);
	}
}
//end basecross
