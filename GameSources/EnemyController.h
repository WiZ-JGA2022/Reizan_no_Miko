/*!
@file EnemyController.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class EnemyController : public GameObject {

		const int m_RandomRange; // �����̍ő�͈�
		const int m_Distance; // ���̕ϐ��ɐݒ肵�����l��Player�Ɨ����
		const int m_DelayCount; // �G�̐����x��

		int m_delayFlame; // 
		int m_enemyCount; // �G�̐�

		int m_sign_x;//�G�̈ʒu�̕���
		int m_sign_z;

		Vec3 m_position; // ���̃I�u�W�F�N�g�̈ʒu���
		Vec3 m_enemyPos; // �G�̈ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		EnemyController(const shared_ptr<Stage>& stage);
		~EnemyController();

		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross
