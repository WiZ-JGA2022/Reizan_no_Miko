/*!
@file SpurtLava.cpp
@brief ���o����n��̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_damageDelayFlame(0),
		m_damageValue(1.0f),
		m_scale(Vec3(5.0f, 5.0f, 5.0f)),
		m_position(0)
	{
	}
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_damageDelayFlame(0),
		m_damageValue(1.0f),
		m_scale(Vec3(5.0f, 5.0f, 5.0f)),
		m_position(position)
	{
	}
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_damageDelayFlame(0),
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

		// �R���W����������
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);
	}

	void SpurtLava::OnUpdate()
	{
		m_damageDelayFlame--;
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