/*!
@file EnemyBullet.h
@brief 敵の弾など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		std::shared_ptr<Transform> m_Transform;

		float m_speed;
		Vec3 m_forward;

		// 弾を発射したオブジェクトへのポインタ
		std::shared_ptr<Enemy> m_owner;
	public:
		EnemyBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<Enemy>& owner) :
			GameObject(stage),
			m_owner(owner),
			m_speed(5.0f),
			m_forward(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // オブジェクトデータの更新
	};


}
