/*!
@file Item.cpp
@brief �A�C�e���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Item::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		auto ItemColl = AddComponent<CollisionObb>();
		ItemColl->SetAfterCollision(AfterCollision::None);

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		MoveExp();
	}

	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
			playerStatus->ExpValueUpdate(m_expValue);
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
	}

	void Item::MoveExp()
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

		m_direction = playerPos - pos; // �v���C���[�Ƃ̋������v�Z

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		m_pickupRange = playerStatus->GetStatusValue(L"PICKUP");

		// �v���C���[�̎擾�͈͓��ɂ��Ȃ����
		if (m_direction.length() > m_pickupRange)
		{
			// �����Ȃ�
			return;
		}

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +
			m_direction.y * m_direction.y +
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// �����܂�

		pos += m_direction * m_speed * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_direction.z, m_direction.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����

	}
}
//end basecross
