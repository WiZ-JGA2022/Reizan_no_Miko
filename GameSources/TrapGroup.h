/*!
@file TrapGroup.h
@brief 罠本体
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	溶岩が吹き出すタイプの罠
	*/
	class SpurtLava : public GameObject {

		// 状態フラグ
		enum class TrapState
		{
			Wait,		// 待機
			Active,		// 実行
			ActiveDelay	// 実行遅延
		};
		enum TrapState m_isState = TrapState::Wait;

		// ダメージが発生するまでの時間
		const int m_DamageActiveDelayFlame = 180;
		// ダメージが発生する間隔
		const int m_DamageIntervalFlame = 50;
		// 消えるまでの時間
		const int m_RemoveDelayCount = 300;

		int m_activeFlame;
		int m_removeDelayFlame;

		Vec3 m_scale; // 大きさ
		Vec3 m_position; // 位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント
		shared_ptr<SoundItem> m_se[2];

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
