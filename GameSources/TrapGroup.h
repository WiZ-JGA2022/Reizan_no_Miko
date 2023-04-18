/*!
@file SpurtLava.h
@brief ���o����n��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	�n�₪�����o���^�C�v���
	*/
	class SpurtLava : public GameObject {

		// �_���[�W��^����Ԋu
		const int m_DamageDelayFlame = 50;
		const int m_RemoveDelayCount = 300;
		int m_removeDelayFlame;

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

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
