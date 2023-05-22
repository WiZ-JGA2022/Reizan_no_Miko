/*!
@file TrapGroup.h
@brief 㩖{��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	�n�₪�����o���^�C�v���
	*/
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
		shared_ptr<SoundItem> m_se[2];

	public:
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;
	};

	/**
	���ނƎh���鞙��ݒu�����
	*/
	class SpikeTrap : public GameObject {

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu���
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpikeTrap();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};

	/**
	�N�U��W�Q����I�u�W�F�N�g��ݒu�����
	*/
	class BlockingStone : public GameObject
	{
		const int m_DefaultDelay;
		const float m_DefaultHp = 100.0f;

		float m_hp;
		int m_delay;

		Vec3 m_objectPosition;

		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;

	public:
		BlockingStone(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultDelay(5),
			m_delay(0),
			m_hp(m_DefaultHp)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void DamageProcess();

		int GetMaxHp()
		{
			return (int)m_DefaultHp;
		}
		float GetCurrentHp()
		{
			return m_hp;
		}

	};
}
