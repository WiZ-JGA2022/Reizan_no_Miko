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
		m_transform->SetScale(m_itemScale);
		m_transform->SetPosition(m_itemPosition);

		auto ItemColl = AddComponent<CollisionObb>();
		ItemColl->SetAfterCollision(AfterCollision::None);

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

		m_direction = playerPos - pos; // �v���C���[�ւ̕������v�Z

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +
			m_direction.y * m_direction.y +
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// �����܂�

		pos += m_direction * m_speed * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����

		////���͈̔͂Ƀv���C���[���������炻�̕����Ɉړ�����
		//auto ItemAreapos = m_inArea;
		//bool IteminArea(false)
		//	if (Playerpos.x > ItemAreapos)
		//	{

		//	}
	}

	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
	}

}
//end basecross
