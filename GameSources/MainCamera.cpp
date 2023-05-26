/*!
@file MyCamera.cpp
@brief �J��������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCamera�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	MyCamera::MyCamera() :
		Camera(),
		m_toTargetLerp(1.0f),
		m_radY(0.5f),
		m_radXZ(0),
		m_CameraUpDownSpeed(0.5f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(10.0f),
		m_RotSpeed(1.0f),
		m_angle(XMConvertToRadians(270.0f))
	{}
	MyCamera::~MyCamera() {}

	void MyCamera::OnCreate() {
		// �����l�̐ݒ�
		auto scene = App::GetApp()->GetScene<Scene>();
		m_radXZ = scene->GetBeforeCameraRadXZ();
		m_radY = scene->GetBeforeCameraRadY();
		m_angle = scene->GetBeforeCameraAngle();
	}

	void MyCamera::OnUpdate() {
	
		// �R���g���[���[�̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		// �Ǐ]����I�u�W�F�N�g�̃|�C���^���擾
		auto ptrTarget = GetTargetObject();
		// �f���^�^�C��
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// Eye��At�̐ݒ�
		Vec3 newEye = GetEye();
		Vec3 newAt = Vec3(
			ptrTarget->GetComponent<Transform>()->GetPosition().x,
			ptrTarget->GetComponent<Transform>()->GetPosition().y + 1.0f, 
			ptrTarget->GetComponent<Transform>()->GetPosition().z
		);

		// �v�Z�Ɏg�����߂̃x�N�g��
		m_armVec = newEye - newAt;
		// ���K��
		m_armVec.normalize();

		// �X�e�B�b�N�̎擾
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbRY = cntlVec[0].fThumbRY;
			fThumbRX = cntlVec[0].fThumbRX;
			wButtons = cntlVec[0].wButtons;
		}

		//�㉺�p�x�̕ύX
		if (cntlVec[0].fThumbRY >= 0.5f ) {
			m_radY += m_CameraUpDownSpeed * elapsedTime;

		}
		else if (cntlVec[0].fThumbRY <= -0.5f ) {
			m_radY -= m_CameraUpDownSpeed * elapsedTime;
		}

		// �����Őݒ肵�������ȏ�ɍs���Ȃ�
		if (m_radY > XM_PI * 4 / 9.0f) {
			m_radY = XM_PI * 4 / 9.0f;
		}
		else if (m_radY <= m_CameraUnderRot) {
			// �J���������E���ɉ��������炻��ȏ㉺����Ȃ�
			m_radY = m_CameraUnderRot;
		}
		m_armVec.y = sin(m_radY); // Y�̈ʒu��ݒ�

		// Y����]���쐬
		if (cntlVec[0].fThumbRX != 0  ) {
			// ��]�X�s�[�h�𔽉f
			if (cntlVec[0].fThumbRX != 0) {
				m_radXZ += -cntlVec[0].fThumbRX * elapsedTime * m_RotSpeed;
			}
		}
		// �N�I�[�^�j�I����Y��]���v�Z
		Quat qtXZ;
		qtXZ.rotation(-m_radXZ, bsm::Vec3(0, 1.0f, 0));
		qtXZ.normalize();
		// �ړ���̍s����v�Z���邱�ƂŁAXZ�̒l���Z�o
		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		// �r�p�x�ɑ��
		m_armVec.x = posXZ.x;
		m_armVec.z = posXZ.z;
		// �r�p�x�𐳋K��
		m_armVec.normalize();

		// �J�����A���O���̐ݒ�
		m_angle += -fThumbRX * elapsedTime;

		// �ڎw�������ꏊ�ɃA�[���̒l�Ƙr�x�N�g����Eye�𒲐�
		Vec3 toEye = newAt + m_armVec * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_toTargetLerp, Lerp::Linear);

		// �ʒu�̍X�V
		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();	
	}
}
//end basecross