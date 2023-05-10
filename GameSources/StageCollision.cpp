/*!
@file StageCollision.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageCollision::StageCollision(const std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	StageCollision::~StageCollision() {}

	void StageCollision::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, 0.0f, 0.0f);
		transComp->SetScale(5.0f, 1.0f, 1.0f);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision::OnUpdate()
	{
	}

}