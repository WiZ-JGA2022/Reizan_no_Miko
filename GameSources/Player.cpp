/*!
@file Player.cpp
@brief ƒvƒŒƒCƒ„[‚È‚ÇÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetOwnShadowActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(Vec3(0.0f));
		AddTag(L"Player");
	}

}
//end basecross

