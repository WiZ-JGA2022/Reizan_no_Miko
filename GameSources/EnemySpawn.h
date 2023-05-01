/*!
@file EnemyController.h
@brief �G�Ȃ�
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

		//�o���p�^�[��
		void Spawn1(Vec3 pos);//1��
		void Spawn2(Vec3 pos);//2��
		void Spawn3(Vec3 pos);//3��
		void Spawn4(Vec3 pos);//4��
		void Spawn5(Vec3 pos);//5��
		void Spawn6(Vec3 pos);//6��
	};

}