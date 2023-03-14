/*!
@file EnemyController.cpp
@brief �G�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void EnemyController::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetOwnShadowActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(Vec3(1.0f));

	}

}
//end basecross
