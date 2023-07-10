/*!
@file Onibi.cpp
@brief �P���ȓ����̓G
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Onibi::Onibi(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60), // �_���[�W��^����Ԋu
		m_RecastCount(120), // ���ˊԊu
		m_damageDelayFlame(m_DamageDelayCount), //
		m_recastFlame(0),  // 
		m_position(position), // �����ʒu
		m_scale(Vec3(1.0f)) // �����T�C�Y
	{
	}
	Onibi::~Onibi() {}

	void Onibi::OnCreate()
	{
		Enemy::CreateEnemyMesh(m_position, m_scale, L"SOUL_MODEL");

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>(); 
		ptrDraw->AddAnimation(L"move", 0, 30, true);
		ptrDraw->ChangeCurrentAnimation(L"move");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionCapsule>();
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		
		AddTag(L"Enemy");

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring damageEffectStr = DataDir + L"Effects\\" + L"damage.efk";
		wstring diedEffectStr = DataDir + L"Effects\\" + L"soul.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_damageEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, damageEffectStr);
		m_diedEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, diedEffectStr);
	}

	void Onibi::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		
		// ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����S�����Ƃ�
		if (playerStatus->GetStatusValue(L"HP") <= 0)
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
		ptrDraw->UpdateAnimation(elapsedTime); // �A�j���[�V�����̍X�V

		// �f�B���C�̌���
		m_damageDelayFlame--;
		m_recastFlame--;

		// �ړ�����
		MoveEnemyPlayer();

		// ���L���X�g�^�C�����I�������
		if (m_recastFlame <= 0)
		{
			// �e�𔭎˂���
			GetStage()->AddGameObject<EnemyBullet>(m_transform->GetPosition(), m_statusValue[L"ATK"]);

			// ���L���X�g�^�C���̔���
			m_recastFlame = m_RecastCount;
		}
	}

	void Onibi::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		
		// ��l���̒e�ɂ���������
		if (other->FindTag(L"PlayerBullet"))
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Start(L"ENEMYDAMAGE_SE", 0, 0.3f);

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
	} // end OnCollisionEnter

	void Onibi::MoveEnemyPlayer()
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		Vec3 pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

		m_direction = playerPos - pos; // �v���C���[�ւ̕������v�Z
		m_direction.normalize(); // ���K��

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_direction.z, m_direction.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void Onibi::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f)); //�G�̖h��͂ɉ����ă_���[�W�̒l�̕ύX
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_damageEffect, m_transform->GetPosition(), Vec3(0.5f));

		// �G��HP����_���[�W�����炷
		m_statusValue[L"HP"] -= totalDamage;
	}

	float Onibi::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}