/*!
@file Ground.cpp
@brief �n�ʂ�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Ground::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"grass"); // �e�N�X�`���}�b�s���O
		drawComp->SetOwnShadowActive(true);	// �e�̉f�荞�݂�������

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -1.0f, 0.0f);
		transComp->SetScale(10.0f, 1.0f, 10.0f);
	}

}
//end basecross
