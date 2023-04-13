/*!
@file SimpleEnemy.cpp
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross {
	SimpleEnemy::SimpleEnemy(const shared_ptr<Stage>& stage, const Vec3& position) :
		Enemy(stage),
		m_position(position),
		m_currentPointIndex(0)
	{
	}
	SimpleEnemy::~SimpleEnemy() {}

	void SimpleEnemy::OnCreate()
	{
		Enemy::OnCreate();
		
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

		if (3 < m_currentPointIndex)
		{
			return;
		}

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		//m_position = m_transform->GetPosition();

		//if (m_position.x - m_points[m_currentPointIndex].x <= m_direction[m_currentPointIndex].x || m_position.z - m_points[m_currentPointIndex].z <= m_direction[m_currentPointIndex].z)
		//{
		//	m_currentPointIndex++;
		//}
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
		m_transform->SetPosition(m_position); // �V�������W�ōX�V����
		
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
}