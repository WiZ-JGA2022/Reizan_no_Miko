/*!
@file Oni.cpp
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Project.h"


namespace basecross {
	Oni::Oni(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(position),
		m_scale(Vec3(3.0f)),
		m_currentPointIndex(0),
		m_alpha(1.0f),
		m_died(false)
	{
	}
	Oni::~Oni() {}

	void Oni::OnCreate()
	{
		Enemy::CreateEnemyMesh(m_position, m_scale, L"ONI");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->AddAnimation(L"walk", 0, 30, true);
		ptrDraw->AddAnimation(L"attack", 35, 30, true);
		ptrDraw->AddAnimation(L"died", 70, 30, false);
		ptrDraw->AddAnimation(L"wait", 105, 30, true);
		ptrDraw->ChangeCurrentAnimation(L"walk");

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		m_diedEffectStr = DataDir + L"Effects\\" + L"soul.efk";
		m_damageEffectStr = DataDir + L"Effects\\" + L"damage.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_diedEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, m_diedEffectStr);
		m_damageEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, m_damageEffectStr);

	}

	void Oni::OnUpdate()
	{
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����Ȃ��Ƃ�
		if (!player->GetDrawActive())
		{
			// �������~����
			return;
		}
		ptrDraw->UpdateAnimation(elapsedTime);
		// HP��0�ɂȂ�����
		if (m_statusValue[L"HP"] <= 0)
		{
			if (!m_died)
			{
				ptrDraw->ChangeCurrentAnimation(L"died");
				//�G�t�F�N�g�̃v���C
				m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_diedEffect, m_transform->GetPosition(), Vec3(0.5f));
				m_died = true;
			}
			if (ptrDraw->IsTargetAnimeEnd() && ptrDraw->GetCurrentAnimation() == L"died")
			{
				// �������~���A�����Ȃ�����
				SetUpdateActive(false);
				SetDrawActive(false);
			}
		}
		m_damageDelayFlame--;


		//�G�̈ړ��̏���
		if (m_currentPointIndex == 0)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 40.0f));
		}
		else if (m_currentPointIndex == 1)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 40.0f));
		}
		else if(m_currentPointIndex == 2)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 20.0f));
		}
		else if(m_currentPointIndex == 3)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 20.0f));
		}
		else if(m_currentPointIndex == 4)
		{
			auto stoneTrans = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone")->GetComponent<Transform>();
			MoveEnemyPoint(Vec3(stoneTrans->GetPosition().x, stoneTrans->GetPosition().y + 1.5f, stoneTrans->GetPosition().z));
		}
	}

	void Oni::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (m_died)
		{
			return;
		}
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		// �e�ɂ���������
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

		if (other->FindTag(L"KeyStone"))
		{
			auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
			ptrDraw->ChangeCurrentAnimation(L"attack");
		}
	} // end OnCollisionEnter

	void Oni::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		if (m_died)
		{
			return;
		}

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
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;

				return;
			}
		}
	} // end OnCollisionEnter

	void Oni::MoveEnemyPoint(const Vec3& point)//�`�F�b�N�|�C���g�Ɍ�������
	{
		if (m_died)
		{
			return;
		}
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		Vec3 pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾

		m_direction = point - pos; // �v���C���[�ւ̕������v�Z
		if (m_direction.x < 0.1f && m_direction.z < 0.1f && m_direction.x > -0.1f && m_direction.z > -0.1f)
		{
			m_currentPointIndex++;
			return;
		}
		m_direction.normalize();

		pos += m_direction * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_direction.z, m_direction.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void Oni::EnemyDamageProcess(float damage)
	{
		if (m_died)
		{
			return;
		}
		//�G�t�F�N�g�̃v���C
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_damageEffect, m_transform->GetPosition(), Vec3(1.0f));

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float Oni::GetEnemyStatus(const wstring& statusKey)
	{
		return m_statusValue[statusKey];
	}
}