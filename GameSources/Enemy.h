/*!
@file Enemy.h
@brief �G�S�̂̐e�N���X
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {

		Vec3 m_position;
		std::vector<Vec3> m_points; // ���`��Ԃ̎n�_�ƏI�_
		Vec3 m_start; // �n�_
		Vec3 m_end; // �I�_

		int m_currentPointIndex; // ���݂̈ړ����C���ԍ�
		float m_speed; // �ړ��̑���

		shared_ptr<Transform> m_transform;

	public:
		Enemy(const shared_ptr<Stage>& stage, 
			const Vec3& position
		);
		~Enemy();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void MoveEnemy();
		void SetPosition(const Vec3& Emitter);
	};
}