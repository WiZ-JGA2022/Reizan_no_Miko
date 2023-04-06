/*!
@file EnemyBullet.h
@brief 敵の弾など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		std::shared_ptr<Transform> m_transform;

		float m_speed;
		Vec3 m_forward;

		Vec3 m_direction; // プレイヤーへの方向
		Vec3 m_position;
		Vec3 m_moveLock;

		// 弾を発射したオブジェクトへのポインタ
		std::shared_ptr<Enemy> m_owner;
	public:
		EnemyBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<Enemy>& owner) :
			GameObject(stage),
			m_owner(owner),
			m_speed(5.0f),
			m_forward(Vec3(0)),
			m_position(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // オブジェクトデータの更新

		virtual Vec3 MoveEnemyBullet();
	};


}
