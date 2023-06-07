/*!
@file EnemyBullet.h
@brief �G�̒e�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		float m_speed; // ���x
		float m_damage; // �_���[�W��

		Vec3 m_position; // ���g�̈ʒu
		Vec3 m_scale; // �傫��
		Vec3 m_direction; // �v���C���[�ւ̕���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g
	public:
		// �R���X�g���N�^
		EnemyBullet(const shared_ptr<Stage>& stage, const Vec3& position, const float& damage) :
			GameObject(stage),
			m_speed(8.0f),
			m_damage(damage),
			m_position(position),
			m_scale(Vec3(0.5f))
		{
		}

		// ������
		void OnCreate() override; 
		// �X�V����
		void OnUpdate() override; 

		// �Փ˔���(�����葱���Ă�����)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);

		// �e�̈ړ�����
		void MoveEnemyBullet();
	};


}
