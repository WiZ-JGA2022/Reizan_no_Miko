/*!
@file Enemy.h
@brief 敵全体の親クラス
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {

		Vec3 m_position;
		std::vector<Vec3> m_points; // 線形補間の始点と終点
		Vec3 m_start; // 始点
		Vec3 m_end; // 終点

		int m_currentPointIndex; // 現在の移動ライン番号
		float m_speed; // 移動の速さ

		shared_ptr<Transform> m_transform;

	public:
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