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

		// �X�e�[�^�X��
		std::map<int, wstring> m_statusName = {
			{0, L"HP"},
			{1, L"ATK"},
			{2, L"DEF"},
			{3, L"SPD"},
		};

		// �X�e�[�^�X�l
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 1.0f},
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

		void MoveEnemy();

		void EnemyDamageProcess();
		float GetEnemyStatus(wstring statusKey);
	};
}