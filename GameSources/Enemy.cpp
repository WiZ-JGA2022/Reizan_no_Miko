/*!
@file Enemy.cpp
@brief �G�S�̂̐e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
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
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(true);

		// �e������
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"WALL_TX");
		drawComp->SetOwnShadowActive(true);

		auto enemyController = GetStage()->GetSharedGameObject<EnemyController>(L"EnemyController");

		AddTag(L"Enemy"/*enemyController->GetEnemyNumber()*/); 
		// ���O�ɐݒ肳�ꂽ������NULL�����ȍ~���w�肷�鐔����+���Z�q�ő����Ƌ󔻒�ɂȂ�
		// Enemy����5�ȍ~�̐�����+�ő����Ƌ󔻒�ɂȂ�?(E:0 n:1 e:2 m:3 y:4 \0:5)

		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		playerStatus->SetEnemyATK(m_statusValue[L"ATK"]);
	}

	void Enemy::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		// ���x���A�b�v�C�x���g��ON�ɂȂ�����
		if (levelUpEvent->GetControllerSprite())
		{
			// �������~����
			return;
		}

		// HP��0�ɂȂ�����
		if (m_statusValue[L"HP"] <= 0)
		{
			// �������~���A�����Ȃ�����
			SetUpdateActive(false);
			SetDrawActive(false);
		}

		MoveEnemy();
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// �e�ɂ���������
		if (Other->FindTag(L"PlayerBullet"))
		{
			// �_���[�W���󂯂�
			EnemyDamageProcess();
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

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void Enemy::EnemyDamageProcess()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float damage = playerStatus->GetStatusValue(L"ATK") - (playerStatus->GetStatusValue(L"ATK") * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= damage;
	}

	float Enemy::GetEnemyStatus(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}
}