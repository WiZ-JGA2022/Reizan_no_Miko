/*!
@file Enemy.h
@brief �G�S�̂̐e�N���X
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {
		
		Vec3 m_position; // �����ʒu
		Vec3 m_direction; // �v���C���[�ւ̕���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 1.0f},
		};

	public:
		Enemy(const shared_ptr<Stage>& stage);

		Enemy(const shared_ptr<Stage>& stage, 
			const Vec3& position
		);
		~Enemy();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		/**
		* �G�̈ړ�����
		*/
		void MoveEnemy();

		/**
		* �G���󂯂�_���[�W�̌v�Z
		*/
		void EnemyDamageProcess();

		/**
		* �C�ӂ̓G�̃X�e�[�^�X���擾����֐�
		* 
		* @param statusKey �擾�������X�e�[�^�X�̖��O
		* 
		* @return �w�肵���X�e�[�^�X�̒l
		*/
		float GetEnemyStatus(wstring statusKey);
	};
}