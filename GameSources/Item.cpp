/*!
@file Item.cpp
@brief ƒAƒCƒeƒ€‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Item::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(4.0f));
		transComp->SetPosition(1.0f, 0.0f, 0.0f);


	}
}
//end basecross
