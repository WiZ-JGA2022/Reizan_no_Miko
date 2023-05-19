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

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision::OnUpdate()
	{
	}

}