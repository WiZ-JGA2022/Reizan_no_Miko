/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerBullet : public GameObject
	{
		std::shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		float m_speed; // ���x
		Vec3 m_forward; // �O�����ւ̃x�N�g��

		
		std::shared_ptr<PlayerController> m_owner; // �e�𔭎˂����I�u�W�F�N�g�ւ̃|�C���^
	public:
		// �R���X�g���N�^
		PlayerBullet(const std::shared_ptr<Stage>& stage, const std::shared_ptr<PlayerController>& owner) :
			GameObject(stage),
			m_speed(10.0f),
			m_owner(owner),
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
