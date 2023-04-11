/*!
@file GimmickController.h
@brief ギミックを出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GimmickController : public GameObject {
		
		enum class GimmickState
		{
			UnActive,
			Active,
			DamageDelay
		};
		enum GimmickState m_isState = GimmickState::UnActive;

		// ギミックを生成する位置
		const Vec3 m_GimmickPosition[10] = {
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

		const int m_GimmickCreateDelaySeconds = 570;
		const int m_GimmickDamageDelayFlame = 180;

		int m_gimmickDamageDelay;

		Vec3 m_gimmickPosition[10] = { Vec3(0)};

		shared_ptr<Transform> m_transform;

	public :
		GimmickController(const shared_ptr<Stage>& stage);
		~GimmickController();

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSpurtLava();
	};
}
