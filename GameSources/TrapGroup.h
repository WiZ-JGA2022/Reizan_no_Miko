/*!
@file SpurtLava.h
@brief 噴出する溶岩
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	溶岩が吹き出すタイプの罠
	*/
	class SpurtLava : public GameObject {

		// ダメージを与える間隔
		const int m_DamageDelayFlame = 50;
		const int m_RemoveDelayCount = 300;
		int m_removeDelayFlame;

		Vec3 m_scale; // 大きさ
		Vec3 m_position; // 位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;
	};

	/**
	踏むと刺さる棘を設置する罠
	*/
	class SpikeTrap : public GameObject {

		Vec3 m_scale; // 大きさ
		Vec3 m_position; // 位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpikeTrap();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
