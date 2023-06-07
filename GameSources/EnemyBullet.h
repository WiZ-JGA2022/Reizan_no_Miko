/*!
@file EnemyBullet.h
@brief 敵の弾など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		float m_speed; // 速度
		float m_damage; // ダメージ量

		Vec3 m_position; // 自身の位置
		Vec3 m_scale; // 大きさ
		Vec3 m_direction; // プレイヤーへの方向

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント
	public:
		// コンストラクタ
		EnemyBullet(const shared_ptr<Stage>& stage, const Vec3& position, const float& damage) :
			GameObject(stage),
			m_speed(8.0f),
			m_damage(damage),
			m_position(position),
			m_scale(Vec3(0.5f))
		{
		}

		// 初期化
		void OnCreate() override; 
		// 更新処理
		void OnUpdate() override; 

		// 衝突判定(当たり続けていたら)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);

		// 弾の移動処理
		void MoveEnemyBullet();
	};


}
