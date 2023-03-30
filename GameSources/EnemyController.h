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
		const int m_DelayCount; 

		int m_delayFlame;

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
