/*!
@file Enemy.h
@brief 敵全体の親クラス
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {
		
		Vec3 m_position; // 初期位置
		Vec3 m_direction; // プレイヤーへの方向

		float m_speed; // 移動速度

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		Enemy(const shared_ptr<Stage>& stage);

		Enemy(const shared_ptr<Stage>& stage, 
			const Vec3& position
		);
		~Enemy();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void MoveEnemy();
		void SetPosition(const Vec3& Emitter);
	};
}