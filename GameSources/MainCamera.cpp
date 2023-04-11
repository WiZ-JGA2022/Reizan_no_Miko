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
		// 注視点の座標
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//注視点からの相対座標(回り込みの角度と注視点からの距離で算出する)
		auto relaivePos = Vec3(0.0f, 7.0f, -15.0f);

		Vec3 eye = at + relaivePos;
		SetEye(eye);
		SetAt(at);
	}
}
