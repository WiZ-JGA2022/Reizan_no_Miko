/*!
@file EnemyController.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyController :public GameObject
	{
		std::shared_ptr<Transform> m_transform;

		std::shared_ptr<Transform> m_playerTrans;
		std::shared_ptr<Player> m_playerObj;

		Vec3 m_playerPos;

		float m_enemyHp;
		float m_enemyATK;
		float m_enemyATKSpeed;
		float m_enemySpped;

	public:
		EnemyController(const std::shared_ptr<Stage>& stage,std::shared_ptr<Player>& player) :
			GameObject(stage),
			m_playerObj(player),
			m_playerPos(0,0,0),
			m_enemyHp(10),
			m_enemyATK(1),
			m_enemyATKSpeed(1),
			m_enemySpped(1)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;
	};


}
//end basecross
