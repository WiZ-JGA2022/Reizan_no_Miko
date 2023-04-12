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
		
		float m_atPos;

		float m_distance;

		std::shared_ptr<Transform> m_targetTrans;

	public:
		MainCamera() :
			m_angle(XMConvertToRadians(270.0f)),
			m_atPos(0),
			m_distance(-15.0f)
		{
		}
		void OnCreate() override;
		void OnUpdate() override;

		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_targetTrans = target->GetComponent<Transform>();
		}

		float GetDistance()
		{
			return m_distance;
		}

		void SetDistance(float distance)
		{
			if (distance < 0)
			{
				m_distance = distance;
			}
			else
			{
				m_distance = -distance;
			}
		}
	};
}
