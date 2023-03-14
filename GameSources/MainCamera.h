/*!
@file MainCamera.h
@brief ƒJƒƒ‰
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MainCamera : public Camera
	{
		float m_angle;
		float m_distance;

		std::shared_ptr<Transform> m_targetTrans;

	public:
		MainCamera() :
			m_angle(XMConvertToRadians(270.0f)),
			m_distance(8.0f)
		{
		}
		void OnCreate() override;
		void OnUpdate() override;

		float GetAngle() const
		{
			return m_angle;
		}

		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_targetTrans = target->GetComponent<Transform>();
		}
	};
}
