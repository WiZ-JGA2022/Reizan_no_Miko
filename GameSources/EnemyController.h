/*!
@file EnemyController.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class EnemyController : public GameObject {

		std::shared_ptr<PlayerController> m_playerObj;

		float m_forceX;
		float m_forceZ;

	public:
		EnemyController(const shared_ptr<Stage>& stage, std::shared_ptr<PlayerController>& player) :
			GameObject(stage),
			m_playerObj(player),
			m_forceX(1),
			m_forceZ(1)
		{

		};

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
