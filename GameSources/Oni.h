/*!
@file Oni.h
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Oni : public Enemy {
		// �G�t�F�N�g
		shared_ptr<EfkEffect> m_diedEffect;
		shared_ptr<EfkEffect> m_damageEffect;
		
		shared_ptr<EfkPlay> m_EfkPlay; // �G�t�F�N�g���s�I�u�W�F�N�g

		wstring m_diedEffectStr;
		wstring m_damageEffectStr;

		Vec3 m_position; // �ʒu
		Vec3 m_scale; // �傫��
		Vec3 m_direction; // ����
		
		int m_currentPointIndex; // ���݂̒ʉߓ_

		// �_���[�W��^����Ԋu
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		bool m_died; // ���S�������ǂ����̃t���O

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		// �R���X�g���N�^
		Oni(const shared_ptr<Stage>& stage, const Vec3& position);
		// �f�X�g���N�^
		~Oni();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

		// �Փˉ�������(���������u��)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		// �Փˉ�������(�������Ă��)
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* �G�̈ړ�����
		* 
		* @param point �ʒu
		*/
		void MoveEnemyPoint(const Vec3& point);

		/**
		* �G���󂯂�_���[�W�̌v�Z
		* 
		* @param damage �_���[�W��
		*/
		void EnemyDamageProcess(float damage);

		/**
		* �C�ӂ̓G�̃X�e�[�^�X���擾����֐�
		*
		* @param statusKey �擾�������X�e�[�^�X�̖��O
		*
		* @return �w�肵���X�e�[�^�X�̒l
		*/
		float GetEnemyStatus(const wstring& statusKey);

	};
}