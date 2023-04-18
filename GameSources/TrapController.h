/*!
@file TrapController.h
@brief 罠を管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapController : public GameObject {
		
		enum class TrapState
		{
			Wait,		// 待機
			Active,		// 実行
			DamageDelay	// 実行遅延
		};
		enum TrapState m_isState = TrapState::Wait;

		// ギミックを生成する位置
		const Vec3 m_TrapPosition[10] = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(5.0f, 0.0f, 8.0f),
			Vec3(6.0f, 0.0f, -16.0f),
			Vec3(10.0f, 0.0f, -2.0f),
			Vec3(10.0f, 0.0f, -12.0f),
			Vec3(-3.0f, 0.0f, -7.0f),
			Vec3(-4.0f, 0.0f, 11.0f),
			Vec3(-9.0f, 0.0f, 1.0f),
			Vec3(-14.0f, 0.0f, -5.0f),
			Vec3(-16.0f, 0.0f, 15.0f)
		};

		// ギミックの大きさ
		const Vec3 m_GimmickScale = {
			Vec3(5.0f, 5.0f, 5.0f)
		};

		const int m_TrapCreateDelaySeconds = 590;
		const int m_TrapDamageDelayFlame = 180;

		int m_trapDamageDelay;

		Vec3 m_trapPosition[10] = { Vec3(0)};

		shared_ptr<Transform> m_transform;

	public :
		TrapController(const shared_ptr<Stage>& stage);
		~TrapController();

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSpurtLava();
		int GetDamageFlame();
		int GetDamageDelay();

	};
}
