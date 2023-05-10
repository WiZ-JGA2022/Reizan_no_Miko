/*!
@file Enemy.cpp
@brief �G�S�̂̐e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_ShotRecastCount(300),
		m_shotRecastFlame(m_ShotRecastCount),
		m_position(0)
	{
	}

	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const Vec3& position
	) :
		GameObject(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_ShotRecastCount(300),
		m_shotRecastFlame(m_ShotRecastCount),
		m_position(position)
	{
	}
	Enemy::~Enemy() {}

	void Enemy::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);
		m_transform->SetScale(Vec3(3.0f, 3.0f, 3.0f));

		// �R���W����������
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(true);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"ONI");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g�̐ݒ�
		auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"ONI");
		drawComp->SetMeshToTransformMatrix(spanMat);
		drawComp->AddAnimation(L"walk", 0, 30, true, 10.0f);
		drawComp->ChangeCurrentAnimation(L"walk");

		AddTag(L"Enemy"); 

		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		group->IntoGroup(GetThis<GameObject>());

		// �`�揇�̕ύX
		SetDrawLayer((int)DrawLayer::Bottom);
	}

	void Enemy::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����Ȃ��Ƃ�
		if (levelUpEvent->GetEventActive() || !player->GetDrawActive())
		{
			// �������~����
			return;
		}
		// HP��0�ɂȂ�����
		if (m_statusValue[L"HP"] <= 0)
		{
			// exp�𗎂Ƃ�
			GetStage()->AddGameObject<Item>(m_transform->GetPosition());
			// �������~���A�����Ȃ�����
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		m_damageDelayFlame--;
		m_shotRecastFlame--;

		MoveEnemy();

		if (m_shotRecastFlame <= 0)
		{
			ShotBullet();
			m_shotRecastFlame = m_ShotRecastCount;
		}
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		// �e�ɂ���������
		if (Other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.1f);

			// �_���[�W���󂯂�
			EnemyDamageProcess();
			return;
		}

	} // end OnCollisionEnter

	void Enemy::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// �v���C���[�ɂ���������
		if (other->FindTag(L"Player"))
		{
			if (m_damageDelayFlame <= 0)
			{
				// �_���[�W��^����
				playerStatus->PlayerDamageProcess(m_statusValue[L"ATK"]);
				m_damageDelayFlame = m_DamageDelayCount;
				return;
			}
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
		float rotationY = atan2f(-m_direction.z, m_direction.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void Enemy::ShotBullet()
	{
		GetStage()->AddGameObject<EnemyBullet>(m_transform->GetPosition(), m_statusValue[L"ATK"]);
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