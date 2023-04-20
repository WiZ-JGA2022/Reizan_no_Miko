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

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpikeTrap();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
