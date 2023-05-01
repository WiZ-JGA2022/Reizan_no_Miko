/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemySpawn :public GameObject
	{


	public:
		EnemySpawn(const shared_ptr<Stage>& stage) :
			GameObject(stage)
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