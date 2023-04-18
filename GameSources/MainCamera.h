/*!
@file MainCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MainCamera : public Camera
	{
		const float m_DefaultAngle = XMConvertToRadians(270.0f);

		float m_angle;
		float m_anglevertical;
		float m_atPos;
		float m_distance;
		float m_fThumR;
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		float m_RadY;
		float m_CameraUpDownSpeed;//カメラの上下スピード
		float m_CameraUnderRot;//カメラを下げる降下限界
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		float m_ZoomSpeed;

		bool m_UDBaseMode;
	

		std::shared_ptr<Transform> m_targetTrans;

	public:
		MainCamera() :
			m_angle(m_DefaultAngle),
			m_anglevertical(m_DefaultAngle),
			m_atPos(0),
			m_distance(-15.0f),
			m_fThumR(0.0f),
			m_ToTargetLerp(1.0f),
			m_RadY(0.5f),
			m_CameraUpDownSpeed(1.0f),
			m_CameraUnderRot(0.1f),
			m_ArmLen(5.0f),
			m_MaxArm(20.0f),
			m_MinArm(2.0f),
			m_ZoomSpeed(0.1f),
			m_UDBaseMode(true)

		{
		}
		//bool GetUDBaseMode() const;//Rスティックの上下変更をBaseモードにするかどうかを得る,Baseモードならtrue（デフォルト）
		bool IsUDBaseMode() const;	//							〃							,Baseモードならtrue
		void OnCreate() override;
		void OnUpdate() override;

		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_targetTrans = target->GetComponent<Transform>();
		}

		float GetAngle() const
		{
			return m_angle;
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
