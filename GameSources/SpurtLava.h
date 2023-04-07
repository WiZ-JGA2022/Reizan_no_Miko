/*!
@file SpurtLava.h
@brief 噴出する溶岩
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpurtLava : public GameObject {

		Vec3 m_position; // このオブジェクトの位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		SpurtLava(const shared_ptr<Stage>& stage);
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};
}
