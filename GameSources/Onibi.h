/*!
@file Oni.h
@brief �P���ȓ����̓G
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Onibi : public Enemy {
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_damageEffect;
		shared_ptr<EfkEffect> m_diedEffect;

		shared_ptr<EfkPlay> m_EfkPlay; //�G�t�F�N�g���s�I�u�W�F�N�g

		Vec3 m_position; // �ʒu
		Vec3 m_scale; // �傫��
		Vec3 m_direction; // ����

		const int m_DamageDelayCount; // �_���[�W��^����Ԋu
		const float m_RecastCount; // �e���ˊԊu

		int m_damageDelayFlame;
		float m_recastFlame;

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 1.0f}
		};

	public:
		Onibi(const shared_ptr<Stage>& stage, const Vec3& position);
		~Onibi();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* ��l���Ɍ������Ĉړ����鏈��
		*/
		void MoveEnemyPlayer();

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