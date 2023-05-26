/*!
@file MyCamera.h
@brief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_targetObject;	// �ڕW�ƂȂ�I�u�W�F�N�g
		shared_ptr<Transform> m_targetTrans;	// �ڕW�̃g�����X�t�H�[��
		// �J�����̏㉺�X�s�[�h
		const float m_CameraUpDownSpeed;
		// �J�����������鉺���p�x
		const float m_CameraUnderRot;
		// �r�̒����̐ݒ�
		const float m_ArmLen;
		// ��]�X�s�[�h
		const float m_RotSpeed;

		// �r�̃x�N�g��
		Vec3 m_armVec;
		// ��Ԓl
		float m_toTargetLerp;	
		// �J�����̈ʒu
		float m_radY;
		float m_radXZ;
		// �J�����A���O��
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
