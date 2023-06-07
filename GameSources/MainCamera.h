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
		// コンストラクタ
		MyCamera();
		// デストラクタ
		virtual ~MyCamera(); 

		// 初期化
		virtual void OnCreate() override;
		// 更新処理
		virtual void OnUpdate() override;

		// カメラが追尾するオブジェクトを取得する関数
		shared_ptr<GameObject> GetTargetObject() const {
			if (!m_targetObject.expired()) {
				return m_targetObject.lock();
			}
			return nullptr;
		}
		// カメラが追尾するオブジェクトを設定する関数
		void SetTargetObject(const shared_ptr<GameObject>& Obj) {
			m_targetObject = Obj;
		}
		// カメラのY方向の位置を取得
		float GetRadY() const
		{
			return m_radY;
		}
		// カメラのXZ方向の位置を取得
		float GetRadXZ() const
		{
			return m_radXZ;
		}
		// カメラのアングルを取得
		float GetAngle()
		{
			return m_angle;
		}
	};
}
//end basecross
