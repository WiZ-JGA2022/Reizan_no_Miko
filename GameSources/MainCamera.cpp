/*!
@file MainCamera.cpp
@brief カメラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void MainCamera::OnCreate() 
	{
		m_defaultPos = Vec3(
			cos(m_angle) * -m_distance,
			7.0f,
			sin(m_angle) * -m_distance
		);
	}

	void MainCamera::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		Vec3 padRStick(-pad.fThumbRX, 0.0f, pad.fThumbRY);

		m_angle += padRStick.x * app->GetElapsedTime();
		

		// 注視点の座標
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		m_atPos += padRStick.z * app->GetElapsedTime();

		auto relativePos = Vec3(
			cos(m_angle) * -m_distance,
			5.0f,
			sin(m_angle) * -m_distance
		);

		////注視点からの相対座標(回り込みの角度と注視点からの距離で算出する)
		//auto relaivePos = Vec3(0.0f, 7.0f, -15.0f);

		Vec3 eye = at + relativePos;
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			eye = at + m_defaultPos;
			m_angle = XMConvertToRadians(270.0f);
		}
		SetEye(eye);
		SetAt(at);
	}
}
