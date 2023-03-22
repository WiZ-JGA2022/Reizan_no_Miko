/*!
@file Ground.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Ground::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"grass"); // テクスチャマッピング
		drawComp->SetOwnShadowActive(true);	// 影の映り込みを許可する

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -1.0f, 0.0f);
		transComp->SetScale(10.0f, 1.0f, 10.0f);
	}

}
//end basecross
