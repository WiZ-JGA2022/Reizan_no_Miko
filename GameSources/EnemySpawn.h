/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemySpawn :public GameObject
	{
		Vec3 m_enemyInterval;

	public:
		EnemySpawn(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_enemyInterval(5.0f,0.0f,5.0f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		//出現パターン
		void Spawn1(Vec3 pos);//1体
		void Spawn2(Vec3 pos);//2体
		void Spawn3(Vec3 pos);//3体
		void Spawn4(Vec3 pos);//4体
		void Spawn5(Vec3 pos);//5体
		void Spawn6(Vec3 pos);//6体
	};

}