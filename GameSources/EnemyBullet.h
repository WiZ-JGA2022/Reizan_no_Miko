/*!
@file EnemyBullet.h
@brief �G�̒e�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		std::shared_ptr<Transform> m_transform;

		float m_speed;
		Vec3 m_forward;

		Vec3 m_direction; // �v���C���[�ւ̕���
		Vec3 m_position;
		Vec3 m_moveLock;

		// �e�𔭎˂����I�u�W�F�N�g�ւ̃|�C���^
		std::shared_ptr<Enemy> m_owner;
	public:
		EnemyBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<Enemy>& owner) :
			GameObject(stage),
			m_owner(owner),
			m_speed(5.0f),
			m_forward(Vec3(0)),
			m_position(Vec3(0))

		{
		}

		void OnCreate() override;
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V

		virtual Vec3 MoveEnemyBullet();
	};


}
