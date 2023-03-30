/*!
@file Enemy.h
@brief 敵全体の親クラス
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {

		shared_ptr<Transform> m_transform;

		Vec3 m_speed;
		Vec3 m_position;

	public:
		Enemy(const shared_ptr<Stage>& stage, 
			const Vec3& position
		);
		~Enemy();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void MoveEnemy();
		void SetPosition(const Vec3& Emitter);
	};
}