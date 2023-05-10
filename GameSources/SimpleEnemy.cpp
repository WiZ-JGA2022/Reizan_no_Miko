/*!
@file SimpleEnemy.cpp
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Project.h"


namespace basecross {
	SimpleEnemy::SimpleEnemy(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_DamageDelayCount(60),
		m_damageDelayFlame(m_DamageDelayCount),
		m_position(position),
		m_currentPointIndex(0)
	{
	}
	SimpleEnemy::~SimpleEnemy() {}

	void SimpleEnemy::OnCreate()
	{
		Enemy::OnCreate();

		//auto pos = GetStage()->AddGameObject<EnemyController>()->SetPos();
		m_position = m_points[0];

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

	}

	void SimpleEnemy::OnUpdate()
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
			//GetStage()->AddGameObject<Item>(m_transform->GetPosition());
			// �������~���A�����Ȃ�����
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		m_damageDelayFlame--;


		//�G�̈ړ��̏���
		if (m_currentPointIndex == 0)
		{
			MoveEnemyPoint(Vec3(20.0f, 1.5f, 20.0f));
		}
		else if (m_currentPointIndex == 1)
		{
			MoveEnemyPoint(Vec3(-20.0f, 1.5f, 20.0f));
			//MoveEnemy();
		}
		else if(m_currentPointIndex >= 2)
		{
			//MoveEnemyPlayer();
			MoveEnemyKeyStone();
		}
	}

	void SimpleEnemy::OnCollisionEnter(shared_ptr<GameObject>& other)
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

	void SimpleEnemy::OnCollisionExcute(shared_ptr<GameObject>& other)
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
			if (m_damageDelayFlame <= 0)
			{
				stone->DamageProcess();
				m_damageDelayFlame = m_DamageDelayCount;

				return;
			}


		}
	} // end OnCollisionEnter

	void SimpleEnemy::MoveEnemy()//�V���v��
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_direction[m_currentPointIndex].x * m_direction[m_currentPointIndex].x +
			m_direction[m_currentPointIndex].y * m_direction[m_currentPointIndex].y +
			m_direction[m_currentPointIndex].z * m_direction[m_currentPointIndex].z);
		m_direction[m_currentPointIndex] *= normalizeMagnification;
		// �����܂�

		m_position += m_direction[m_currentPointIndex] * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_direction[m_currentPointIndex].z, m_direction[m_currentPointIndex].x); // ��]�̌v�Z

		m_transform->SetRotation(0.0f, rotationY, 0.0f);
		m_transform->SetPosition(m_position);

		for (int i = 0; i < 1; i++)
		{
			if (m_currentPointIndex == 0)
			{
				if ((int)m_position.z == (int)m_points[m_currentPointIndex + 1].z)
				{
					m_currentPointIndex++;
					break;
				}
				break;
			}
			if ((int)m_position.x == (int)m_points[m_currentPointIndex + 1].x)
			{
				m_currentPointIndex++;
				break;
			}
		}
	}

	void SimpleEnemy::MoveEnemyPoint(Vec3 point)//�`�F�b�N�|�C���g�Ɍ�������
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto pointPos = point;

		Vec3 positionControl(0.0f, 0.0f, 0.0f);
		m_directionPoint = pointPos + positionControl - pos; // �v���C���[�ւ̕������v�Z

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_directionPoint.x * m_directionPoint.x +
			m_directionPoint.y * m_directionPoint.y +
			m_directionPoint.z * m_directionPoint.z);
		m_directionPoint *= normalizeMagnification;
		// �����܂�

		pos += m_directionPoint * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_directionPoint.z, m_directionPoint.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����

		for (int i = 0; i < 1; i++)
		{
			if (m_currentPointIndex == 0)
			{
				if (point.z >= pos.z)
				{
					m_currentPointIndex++;
					break;
				}
			}
			if (m_currentPointIndex == 1)
			{
				if (point.x >= pos.x)
				{
					m_currentPointIndex++;
					break;
				}
			}
			
		}
	}


	void SimpleEnemy::MoveEnemyPlayer()//�v���C���[�Ɍ�������
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾
		auto playerScale = playerTrans->GetScale();

		Vec3 positionControl(0.0f, playerScale.y, 0.0f);
		m_directionPlayer = playerPos + positionControl - pos; // �v���C���[�ւ̕������v�Z

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_directionPlayer.x * m_directionPlayer.x +
			m_directionPlayer.y * m_directionPlayer.y +
			m_directionPlayer.z * m_directionPlayer.z);
		m_directionPlayer *= normalizeMagnification;
		// �����܂�

		pos += m_directionPlayer * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_directionPlayer.z, m_directionPlayer.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}

	void SimpleEnemy::MoveEnemyKeyStone()//�v�΂Ɍ�������
	{
		// �f���^�^�C���̎擾
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// �e��x�N�g���̎擾
		auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
		auto stoneTrans = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone")->GetComponent<Transform>();
		auto stonePos = stoneTrans->GetPosition(); // �v�΂̈ʒu�x�N�g�����擾

		auto stoneScale = stoneTrans->GetScale();// �v�΂̃X�P�[�����擾
		Vec3 positionControl(0.0f, stoneScale.y, 0.0f);//�v�΂̈ʒu����
		Vec3 stonePosition = stonePos + (positionControl / 2);
		m_directionKeyStone = stonePosition - pos; // �v�΂ւ̕������v�Z

		// �x�N�g���̐��K������
		float normalizeMagnification = 1 / sqrt(
			m_directionKeyStone.x * m_directionKeyStone.x +
			m_directionKeyStone.y * m_directionKeyStone.y +
			m_directionKeyStone.z * m_directionKeyStone.z);
		m_directionKeyStone *= normalizeMagnification;
		// �����܂�

		pos += m_directionKeyStone * m_statusValue[L"SPD"] * delta;	// �ړ��̌v�Z
		float rotationY = atan2f(-m_directionKeyStone.z, m_directionKeyStone.x); // ��]�̌v�Z

		m_transform->SetPosition(pos); // �ړ�����
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
	}


	void SimpleEnemy::EnemyDamageProcess(float damage)
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));

		m_statusValue[L"HP"] -= totalDamage;
	}

	float SimpleEnemy::GetEnemyStatus(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}
}