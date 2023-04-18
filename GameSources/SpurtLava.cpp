/*!
@file SpurtLava.cpp
@brief 噴出する溶岩の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_removeDelayFlame(m_RemoveDelayCount),
		m_scale(scale),
		m_position(position)
	{
	}
	SpurtLava::~SpurtLava() {}

	void SpurtLava::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpurtLava");
	}

	void SpurtLava::OnUpdate()
	{
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		ptrColl->SetDrawActive(false);

		m_removeDelayFlame--;
		if (m_removeDelayFlame % 50 == 0)
		{
			ptrColl->SetUpdateActive(true);
			ptrColl->SetDrawActive(true);
		}
		if (m_removeDelayFlame <= 0)
		{
			GetStage()->RemoveGameObject<SpurtLava>(GetThis<SpurtLava>());
		}
	}

	//void SpurtLava::OnCollisionEnter(shared_ptr<GameObject>& other)
	//{
	//	if (other->FindTag(L"Enemy"))
	//	{
	//		if (m_damageDelayFlame <= 0)
	//		{
	//			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
	//			playerStatus->PlayerDamageProcess(m_damageValue);
	//			m_damageDelayFlame = m_DamageDelayCount;
	//			return;
	//		}
	//	}
	//}

	//void SpurtLava::OnCollisionExcute(shared_ptr<GameObject>& other)
	//{
	//	if (other->FindTag(L"Enemy"))
	//	{
	//		if (m_damageDelayFlame <= 0)
	//		{
	//			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
	//			playerStatus->PlayerDamageProcess(m_damageValue);
	//			m_damageDelayFlame = m_DamageDelayCount;
	//			return;
	//		}
	//	}
	//}

	// スパイクトラップクラス
	SpikeTrap::SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_damageValue(5.0f),
		m_scale(scale),
		m_position(position)
	{
	}
	SpikeTrap::~SpikeTrap() {}

	void SpikeTrap::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SPIKE");

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpikeTrap");

		SetAlphaActive(true);
	}

	void SpikeTrap::OnUpdate()
	{
	}

	void SpikeTrap::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Enemy"))
		{
			GetStage()->RemoveGameObject<SpikeTrap>(GetThis<SpikeTrap>());
		}
	}

	float SpikeTrap::GetDamage()
	{
		return m_damageValue;
	}
}