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
		// �����_�̍��W
		Vec3 at = m_targetTrans ? m_targetTrans->GetPosition() : GetAt();

		//�����_����̑��΍��W(��荞�݂̊p�x�ƒ����_����̋����ŎZ�o����)
		auto relaivePos = Vec3(0.0f, 7.0f, -15.0f);

		Vec3 eye = at + relaivePos;
		SetEye(eye);
		SetAt(at);
	}
}
