/*!
@file PlayerBullet.h
@brief �v���C���[�̒e
@prod ��I�t
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBullet : public GameObject
	{
		float m_speed; // ���x
		Vec3 m_forward; // �O�����ւ̃x�N�g��

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		// �R���X�g���N�^
		PlayerBullet(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(10.0f),
			m_forward(Vec3(0))

		{
		}

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

		// �Փˉ�������(�������Ă����)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
