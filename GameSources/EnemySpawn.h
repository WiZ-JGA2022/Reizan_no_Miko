/*!
@file EnemyController.h
@brief “G‚È‚Ç
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
	};

}