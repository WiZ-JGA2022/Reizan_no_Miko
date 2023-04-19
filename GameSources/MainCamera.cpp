/*!
@file MainCamera.cpp
@brief カメラ
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

		// 注視点の座標
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//計算に使うための腕角度（ベクトル）
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();

		//計算に使うための腕角度（ベクトル）
		//bsm::Vec3 armVec = newEye - newAt;

		//縦カメラ
		//auto fThumbRY = m_fThumR;
		//auto fThumbRX = m_fThumR;
		//WORD wButtons = 0;
		//if (cntlVec[0].bConnected) {
		//	fThumbRY = cntlVec[0].fThumbRY;
		//	fThumbRX = cntlVec[0].fThumbRX;
		//	wButtons = cntlVec[0].wButtons;
		//}
		//右スティックのカメラの上下角度変更
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
			//カメラが限界下に下がったらそれ以上下がらない
			m_RadY = m_CameraUnderRot;
		}

		////注視点からの相対座標(回り込みの角度と注視点からの距離で算出する)
		auto relativePos = Vec3(
			cos(m_angle) * -m_distance,
			sin(m_RadY),
			sin(m_angle) * -m_distance
		);
		relativePos.normalize();

		if (pad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ) {
			//カメラ位置を引く
			m_ArmLen += m_ZoomSpeed;
			if (m_ArmLen >= m_MaxArm) {
				//m_MaxArm以上離れないようにする
				m_ArmLen = m_MaxArm;
			}
		}

		if (pad.wButtons & XINPUT_GAMEPAD_DPAD_UP ) {
			//カメラ位置を寄る
			m_ArmLen -= m_ZoomSpeed;
			if (m_ArmLen <= m_MinArm) {
				//m_MinArm以下近づかないようにする
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

