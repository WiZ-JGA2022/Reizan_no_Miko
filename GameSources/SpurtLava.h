/*!
@file SpurtLava.h
@brief 噴出する溶岩
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpurtLava : public GameObject {

		// ダメージを与える間隔
		const int m_DamageDelayCount = 20;
		int m_damageDelayFlame;

		float m_damageValue; // ダメージ量

		Vec3 m_scale; // 大きさ
		Vec3 m_position; // 位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		SpurtLava(const shared_ptr<Stage>& stage);
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

	};
}
