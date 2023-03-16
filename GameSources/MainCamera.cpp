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
		//wstringstream wss;

		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];

		Vec3 padRStick(-pad.fThumbRX, 0.0f, pad.fThumbRY);

		// �X�e�B�b�N�̌X���ɉ����Ċp�x���X�V����
		m_angle += padRStick.x * app->GetElapsedTime();

		// �����_�̍��W
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//�����_����̑��΍��W(��荞�݂̊p�x�ƒ����_����̋����ŎZ�o����)
		auto relaivePos = Vec3(
			cos(m_angle) * m_distance,
			4.0f,
			sin(m_angle) * m_distance);

		Vec3 eye = at + relaivePos;
		SetEye(eye);
		SetAt(at);

	}
}
