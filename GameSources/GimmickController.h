/*!
@file GimmickController.h
@brief ギミックを出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GimmickController : public GameObject {
		
		const Vec3 m_GimmickPosition[10] = {
			Vec3(5.0f, 0.0f, 8.0f),
			Vec3(10.0f, 0.0f, -2.0f),
			Vec3(-9.0f, 0.0f, 1.0f),
			Vec3(-3.0f, 0.0f, -7.0f),
			Vec3(-14.0f, 0.0f, -5.0f),
			Vec3(-16.0f, 0.0f, 15.0f),
			Vec3(6.0f, 0.0f, -16.0f),
			Vec3(-4.0f, 0.0f, 11.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(10.0f, 0.0f, -12.0f)
		};

		const Vec3 m_GimmickScale = {
			Vec3(5.0f, 5.0f, 5.0f)
		};

		shared_ptr<Transform> m_transform;

	public :
		GimmickController(const shared_ptr<Stage>& stage);
		~GimmickController();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
