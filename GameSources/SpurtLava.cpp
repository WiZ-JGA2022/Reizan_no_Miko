/*!
@file SpurtLava.cpp
@brief ���o����n��̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_position(0)
	{
	}
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	SpurtLava::~SpurtLava() {}

	void SpurtLava::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void SpurtLava::OnUpdate()
	{

	}

	void SpurtLava::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{

	}
}