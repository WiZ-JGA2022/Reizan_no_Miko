/*!
@file Oni.cpp
@brief �P���ȓ����̓G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Onibi::Onibi(const shared_ptr<Stage>& stage) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(Vec3 (2,2,2)),
		m_scale(Vec3(3.0f))
	{
	}
	Onibi::~Onibi() {}

	void Onibi::OnCreate()
	{
		Enemy::CreateEnemyMesh(m_position, m_scale, L"ONI_WALK", L"walk");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);

	}

	void Onibi::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
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
			// �������~���A�����Ȃ�����
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		m_damageDelayFlame--;

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);

		Onibi::MoveEnemyPlayer();
	}

	void Onibi::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// �e�ɂ���������
		if (other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.1f);

			// �_���[�W���󂯂�(�_���[�W�ʂ̓v���C���[�̍U���͈ˑ�)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}

		// 㩂ɂ���������
		if (other->FindTag(L"SpikeTrap"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"SPIKEDAMAGE_SE", 0, 0.3f);

			// �_���[�W���󂯂�(�_���[�W�ʂ̓v���C���[�̍U���͈ˑ�)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}

		// �n��ɂ���������
		if (other->FindTag(L"SpurtLava"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"SPIKEDAMAGE_SE", 0, 0.3f);

			// �_���[�W���󂯂�(�_���[�W�ʂ̓v���C���[�̍U���͈ˑ�)
			EnemyDamageProcess(playerStatus->GetStatusValue(L"ATK"));
		}
	} // end OnCollisionEnter

	void Onibi::OnCollisionExcute(shared_ptr<GameObject>& other)
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

		if (other->FindTag(L"KeyStone"))
		{
			auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
			Enemy::ChangeEnemyAnimation(L"ONI_ATTACK", L"attack");
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;

				return;
			}
		}
	} // end OnCollisionEnter

	void Onibi::MoveEnemyPlayer()//�`�F�b�N�|�C���g�Ɍ�������
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		Vec3 pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾
		playerPos.y + 5;

		m_directionPoint = playerPos - pos; // �v���C���[�ւ̕������v�Z
		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_directionPlayer.x * m_directionPlayer.x +
			m_directionPlayer.y * m_directionPlayer.y +
			m_directionPlayer.z * m_directionPlayer.z);
		m_directionPlayer *= normalizeMagnification;

		pos += m_directionPoint * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_directionPoint.z, m_directionPoint.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void Onibi::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float Onibi::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}