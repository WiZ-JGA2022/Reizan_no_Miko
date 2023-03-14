/*!
@file EnemyController.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyController :public GameObject
	{
		float m_enemyHp;
		float m_enemyATK;
		float m_enemyATKSpeed;
		float m_enemySpped;

	public:
		EnemyController(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_enemyHp(10),
			m_enemyATK(1),
			m_enemyATKSpeed(1),
			m_enemySpped(1)
		{
		}

		void OnCreate() override;
	};


}
//end basecross
