/*!
@file SimpleEnemy.h
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SimpleEnemy : public Enemy {

		Vec3 m_position;

		Vec3 m_direction[3] = {
			Vec3(0.0f, 0.0f, -40.0f),
			Vec3(-40.0f, 0.0f, 0.0f),
			Vec3(20.0f, 0.0f, -30.0f)
		};

		Vec3 m_points[4] = {
			Vec3(20.0f, 0.0f, 40.0f),
			Vec3(20.0f, 0.0f, 20.0f),
			Vec3(-20.0f, 0.0f, 20.0f),
			Vec3(0.0f, 0.0f, -10.0f)
		};
		
		int m_currentPointIndex;

		// �_���[�W��^����Ԋu
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

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
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* �G�̈ړ�����
		*/
		void MoveEnemy() override;

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