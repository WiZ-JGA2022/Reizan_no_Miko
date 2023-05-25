/*!
@file Oni.h
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Oni : public Enemy {
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_diedEffect;
		shared_ptr<EfkEffect> m_damageEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		wstring m_diedEffectStr;
		wstring m_damageEffectStr;

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_direction;
		
		int m_currentPointIndex;

		// �_���[�W��^����Ԋu
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		float m_alpha;
		bool m_died;

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		Oni(const shared_ptr<Stage>& stage, const Vec3& position);
		~Oni();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* �G�̈ړ�����
		*/
		void MoveEnemyPoint(const Vec3& point);//point

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
		float GetEnemyStatus(const wstring& statusKey);

	};
}