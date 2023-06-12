/*!
@file TrapGroup.h
@brief 㩖{��
@prod ��I�t
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	// �n�₪�����o���^�C�v���
	class SpurtLava : public GameObject {
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		// ��ԃt���O
		enum class TrapState
		{
			Wait,		// �ҋ@
			Active,		// ���s
			ActiveDelay	// ���s�x��
		};
		enum TrapState m_isState = TrapState::Wait;

		// �_���[�W����������܂ł̎���
		const int m_DamageActiveDelayFlame = 180;
		// �_���[�W����������Ԋu
		const int m_DamageIntervalFlame = 50;
		// ������܂ł̎���
		const int m_RemoveDelayCount = 300;

		int m_activeFlame;
		int m_removeDelayFlame;

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g
		shared_ptr<SoundItem> m_se[2]; // �T�E���h�A�C�e��

	public:
		// �R���X�g���N�^
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		// �f�X�g���N�^
		~SpurtLava();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};

	// ���ނƎh���鞙��ݒu�����
	class SpikeTrap : public GameObject {
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		// �R���X�g���N�^
		SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		// �f�X�g���N�^
		~SpikeTrap();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
