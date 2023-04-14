/*!
@file MainCamera.cpp
@brief �J����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void MainCamera::OnCreate() 
	{
	}

	void MainCamera::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		Vec3 padRStick(-pad.fThumbRX, 0.0f, pad.fThumbRY);

		m_angle += padRStick.x * app->GetElapsedTime();
		

		// �����_�̍��W
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		m_atPos += padRStick.z * app->GetElapsedTime();

		////�����_����̑��΍��W(��荞�݂̊p�x�ƒ����_����̋����ŎZ�o����)
		auto relativePos = Vec3(
			cos(m_angle) * -m_distance,
			5.0f,
			sin(m_angle) * -m_distance
		);


		Vec3 eye = at + relativePos;
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			m_angle = m_DefaultAngle;
		}
		SetEye(eye);
		SetAt(at);
	}
}
