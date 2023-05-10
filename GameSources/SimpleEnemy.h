/*!
@file SimpleEnemy.h
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class SimpleEnemy : public Enemy {

		Vec3 m_position;

		Vec3 m_randomDirection;
		Vec3 m_randomPosition;

		Vec3 m_direction[3] = {
			Vec3(0.0f, 0.0f, -40.0f),
			Vec3(-20.0f, 0.0f, 0.0f),
			Vec3(20.0f, 0.0f, -30.0f)
		};

		Vec3 m_points[4] = {
			Vec3(20.0f, 1.5f, 40.0f),
			Vec3(20.0f, 1.5f, 20.0f),
			Vec3(-20.0f, 1.5f, 20.0f),
			Vec3(0.0f, 1.5f, 0.0f)
		};
		
		int m_currentPointIndex;

		// �_���[�W��^����Ԋu
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		Vec3 m_directionPoint;
		Vec3 m_directionPlayer;
		Vec3 m_directionKeyStone;
		Vec3 m_directionBlockingStone;

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		SimpleEnemy(const shared_ptr<Stage>& stage, const Vec3& position);
		~SimpleEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* �G�̈ړ�����
		*/
		void MoveEnemy() override;
		void MoveEnemyPoint(Vec3 point);//point
		void MoveEnemyPlayer();//player
		void MoveEnemyKeyStone();//keystone
		void MoveEnemyBlockingStone();//blockingStone

		/**
		* �G���󂯂�_���[�W�̌v�Z
		*/
		void EnemyDamageProcess(float damage);

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