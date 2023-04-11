/*!
@file SpurtLava.cpp
@brief ï¨èoÇ∑ÇÈónä‚ÇÃé¿ëï
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_damageDelayFlame(0),
		m_removeDelayFlame(m_RemoveDelayCount),
		m_damageValue(1.0f),
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

		// ÉRÉäÉWÉáÉìÇÇ¬ÇØÇÈ
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);
		// è’ìÀîªíËÇÕNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);
	}

	void SpurtLava::OnUpdate()
	{
		m_damageDelayFlame--;
		m_removeDelayFlame--;
		if (m_removeDelayFlame <= 0)
		{
			GetStage()->RemoveGameObject<SpurtLava>(GetThis<SpurtLava>());
		}
	}

	void SpurtLava::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			if (m_damageDelayFlame <= 0)
			{
				auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
				playerStatus->PlayerDamageProcess(m_damageValue);
				m_damageDelayFlame = m_DamageDelayCount;
				return;
			}
		}
	}

	void SpurtLava::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			if (m_damageDelayFlame <= 0)
			{
				auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
				playerStatus->PlayerDamageProcess(m_damageValue);
				m_damageDelayFlame = m_DamageDelayCount;
				return;
			}
		}
	}
}