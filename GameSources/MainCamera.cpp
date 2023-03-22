/*!
@file MainCamera.cpp
@brief カメラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void MainCamera::OnCreate() 
	{
	}

	void MainCamera::OnUpdate()
	{
		//wstringstream wss;

		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];

		Vec3 padRStick(-pad.fThumbRX, 0.0f, pad.fThumbRY);

		// スティックの傾きに応じて角度を更新する
		m_angle += padRStick.x * app->GetElapsedTime();

		// 注視点の座標
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//注視点からの相対座標(回り込みの角度と注視点からの距離で算出する)
		auto relaivePos = Vec3(
			cos(m_angle) * m_distance,
			4.0f,
			sin(m_angle) * m_distance);

		Vec3 eye = at + relaivePos;
		SetEye(eye);
		SetAt(at);

	}
}
