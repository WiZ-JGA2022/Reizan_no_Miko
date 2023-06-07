/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBullet : public GameObject
	{
		std::shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		float m_speed; // 速度
		Vec3 m_forward; // 前方向へのベクトル

		
		std::shared_ptr<PlayerController> m_owner; // 弾を発射したオブジェクトへのポインタ
	public:
		// コンストラクタ
		PlayerBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<PlayerController>& owner) :
			GameObject(stage),
			m_speed(10.0f),
			m_owner(owner),
			m_forward(Vec3(0))

		{
		}

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;

		// 衝突応答処理(当たっている間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
