/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBullet : public GameObject
	{
		std::shared_ptr<Transform> m_Transform;

		float m_speed;
		Vec3 m_forward;

		// 弾を発射したオブジェクトへのポインタ
		std::shared_ptr<PlayerController> m_owner;
	public:
		PlayerBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<PlayerController>& owner) :
			GameObject(stage),
			m_speed(10.0f),
			m_owner(owner),
			m_forward(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // オブジェクトデータの更新

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
