/*!
@file Enemy.cpp
@brief �G�S�̂̐e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_speed(1.0f),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_speed(1.0f),
		m_position(position)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����Auto
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(true);

		// �e������
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"WALL_TX");
		drawComp->SetOwnShadowActive(true);


		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());


	}

	void Enemy::OnUpdate()
	{
		MoveEnemy();
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// �e�ɂ���������(�e�X�g�p��player)
		if (Other->FindTag(L"Player"))
		{
			// �������~���A�����Ȃ�����
			//SetUpdateActive(false);
			//SetDrawActive(false);
			return;
		}

	} // end OnCollisionEnter

	void Enemy::MoveEnemy()
	{
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
	}

	void Enemy::SetPosition(const Vec3& Emitter)
	{
		//m_transform->ResetPosition(Emitter);
		GetStage()->RemoveGameObject<Enemy>(NULL);

		SetUpdateActive(true);
		SetDrawActive(true);
	}
}