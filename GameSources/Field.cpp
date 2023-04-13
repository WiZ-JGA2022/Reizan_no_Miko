/*!
@file Ground.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Field::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -1.0f, 0.0f);
		//transComp->SetScale(1.0f, 1.0f, 1.0f);
		transComp->SetScale(100.0f, 1.0f, 100.0f);

		//Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		//spanMat.affineTransformation(
		//	Vec3(1.0f, 1.0f, 1.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);
		////影をつける（シャドウマップを描画する）
		//auto ptrShadow = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(L"STAGE");
		//ptrShadow->SetMeshToTransformMatrix(spanMat);

		//auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		//drawComp->SetFogEnabled(true);
		//drawComp->SetMeshResource(L"STAGE");
		//drawComp->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

	}

	void Field::OnUpdate()
	{
		//auto transComp = GetComponent<Transform>();
		//transComp->ResetPosition(Vec3(0.0f, -5.5f, 5.0f));
	}
}
//end basecross
