/*!
@file StageCollision.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageCollision::StageCollision(const std::shared_ptr<Stage>& stage, const Vec3& position,const Vec3& scale) :
		GameObject(stage),
		m_position(position),
		m_scale(scale)
	{
	}
	StageCollision::~StageCollision() {}

	void StageCollision::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		// 位置情報の設定
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);

		// 見た目の設定
		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		// 描画レイヤーを設定
		SetDrawLayer((int)DrawLayer::MostBottom);

		// タグを追加
		AddTag(L"Stage");
	}

	void StageCollision::OnUpdate()
	{
	}

}