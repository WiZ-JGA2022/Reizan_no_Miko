/*!
@file MainCamera.cpp
@brief �J����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	bool MainCamera::IsUDBaseMode() const {
		return m_UDBaseMode;
	}

	void MainCamera::OnCreate()
	{
	}

	void MainCamera::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		Vec3 padRStick(-pad.fThumbRX, pad.fThumbRX, pad.fThumbRY);

		m_angle += padRStick.x * app->GetElapsedTime();
		m_anglevertical += padRStick.z * app->GetElapsedTime();

		// �����_�̍��W
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//�v�Z�Ɏg�����߂̘r�p�x�i�x�N�g���j
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();

		//�v�Z�Ɏg�����߂̘r�p�x�i�x�N�g���j
		//bsm::Vec3 armVec = newEye - newAt;

		//�c�J����
		//auto fThumbRY = m_fThumR;
		//auto fThumbRX = m_fThumR;
		//WORD wButtons = 0;
		//if (cntlVec[0].bConnected) {
		//	fThumbRY = cntlVec[0].fThumbRY;
		//	fThumbRX = cntlVec[0].fThumbRX;
		//	wButtons = cntlVec[0].wButtons;
		//}
		//�E�X�e�B�b�N�̃J�����̏㉺�p�x�ύX
		if (padRStick.z >= 0.1f )//{
			if (IsUDBaseMode()) {
				m_RadY += m_CameraUpDownSpeed * elapsedTime;
			}
			else {
				m_RadY -= m_CameraUpDownSpeed * elapsedTime;
			}

		else if (padRStick.z<= -0.1f ) {
			if (IsUDBaseMode()) {
				m_RadY -= m_CameraUpDownSpeed * elapsedTime;
			}
			else {
				m_RadY += m_CameraUpDownSpeed * elapsedTime;
			}
		}
		if (m_RadY > XM_PI * 4 / 9.0f) {
			m_RadY = XM_PI * 4 / 9.0f;
		}
		else if (m_RadY <= m_CameraUnderRot) {
			//�J���������E���ɉ��������炻��ȏ㉺����Ȃ�
			m_RadY = m_CameraUnderRot;
		}

		////�����_����̑��΍��W(��荞�݂̊p�x�ƒ����_����̋����ŎZ�o����)
		auto relativePos = Vec3(
			cos(m_angle) * -m_distance,
			sin(m_RadY),
			sin(m_angle) * -m_distance
		);
		relativePos.normalize();

		if (pad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ) {
			//�J�����ʒu������
			m_ArmLen += m_ZoomSpeed;
			if (m_ArmLen >= m_MaxArm) {
				//m_MaxArm�ȏ㗣��Ȃ��悤�ɂ���
				m_ArmLen = m_MaxArm;
			}
		}

		if (pad.wButtons & XINPUT_GAMEPAD_DPAD_UP ) {
			//�J�����ʒu�����
			m_ArmLen -= m_ZoomSpeed;
			if (m_ArmLen <= m_MinArm) {
				//m_MinArm�ȉ��߂Â��Ȃ��悤�ɂ���
				m_ArmLen = m_MinArm;
			}
		}

		Vec3 eye = at + relativePos * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), eye, 0, 1.0f, m_ToTargetLerp, Lerp::Linear);

		if ( pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER || pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			m_angle = m_DefaultAngle;
		}
		SetEye(newEye);
		SetAt(at);

	}

}

