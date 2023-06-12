/*!
@file PlayerBullet.h
@brief プレイヤーの弾
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBullet : public GameObject
	{
		float m_speed; // 速度
		Vec3 m_forward; // 前方向へのベクトル

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		// コンストラクタ
		PlayerBullet(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(10.0f),
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
