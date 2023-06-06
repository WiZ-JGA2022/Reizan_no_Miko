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
		// �R���X�g���N�^
		MyCamera();
		// �f�X�g���N�^
		virtual ~MyCamera(); 

		// ������
		virtual void OnCreate() override;
		// �X�V����
		virtual void OnUpdate() override;

		// �J�������ǔ�����I�u�W�F�N�g���擾����֐�
		shared_ptr<GameObject> GetTargetObject() const {
			if (!m_targetObject.expired()) {
				return m_targetObject.lock();
			}
			return nullptr;
		}
		// �J�������ǔ�����I�u�W�F�N�g��ݒ肷��֐�
		void SetTargetObject(const shared_ptr<GameObject>& Obj) {
			m_targetObject = Obj;
		}
		// �J������Y�����̈ʒu���擾
		float GetRadY() const
		{
			return m_radY;
		}
		// �J������XZ�����̈ʒu���擾
		float GetRadXZ() const
		{
			return m_radXZ;
		}
		// �J�����̃A���O�����擾
		float GetAngle()
		{
			return m_angle;
		}
	};
}
//end basecross
