/*!
@file MyCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_targetObject;	// 目標となるオブジェクト
		shared_ptr<Transform> m_targetTrans;	// 目標のトランスフォーム
		// カメラの上下スピード
		const float m_CameraUpDownSpeed;
		// カメラを下げる下限角度
		const float m_CameraUnderRot;
		// 腕の長さの設定
		const float m_ArmLen;
		// 回転スピード
		const float m_RotSpeed;

		// 腕のベクトル
		Vec3 m_armVec;
		// 補間値
		float m_toTargetLerp;	
		// カメラの位置
		float m_radY;
		float m_radXZ;
		// カメラアングル
		float m_angle;


	public:
		MyCamera();
		virtual ~MyCamera();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		shared_ptr<GameObject> GetTargetObject() const {
			if (!m_targetObject.expired()) {
				return m_targetObject.lock();
			}
			return nullptr;
		}
		void SetTargetObject(const shared_ptr<GameObject>& Obj) {
			m_targetObject = Obj;
		}

		float GetRadY() const
		{
			return m_radY;
		}

		float GetRadXZ() const
		{
			return m_radXZ;
		}

		float GetAngle()
		{
			return m_angle;
		}
	};
}
//end basecross
