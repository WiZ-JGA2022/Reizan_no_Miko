/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerShot : public GameObject
	{
		std::shared_ptr<Transform> m_Transform;

		float m_speed;
		Vec3 m_forward;

		// 弾を発射したオブジェクトへのポインタ
		std::shared_ptr<PlayerController> m_owner;
	public:
		PlayerShot(const std::shared_ptr<Stage>& stage, const std::shared_ptr<PlayerController>& owner) :
			GameObject(stage),
			m_speed(5.0f),
			m_owner(owner),
			m_forward(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // オブジェクトデータの更新
	};

	class PlayerHomingShot : public GameObject
	{
		std::shared_ptr<Transform> m_Transform;

		float m_speed;
		Vec3 m_forward;

		// 弾を発射したオブジェクトへのポインタ
		std::shared_ptr<PlayerController> m_owner;
	public:
		PlayerHomingShot(const std::shared_ptr<Stage>& stage, const std::shared_ptr<PlayerController>& owner) :
			GameObject(stage),
			m_speed(5.0f),
			m_owner(owner),
			m_forward(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // オブジェクトデータの更新
	};

}
