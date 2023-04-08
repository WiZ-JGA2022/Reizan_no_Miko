/*!
@file SpurtLava.h
@brief ���o����n��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpurtLava : public GameObject {

		// �_���[�W��^����Ԋu
		const int m_DamageDelayCount = 20;
		int m_damageDelayFlame;

		float m_damageValue; // �_���[�W��

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		SpurtLava(const shared_ptr<Stage>& stage);
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

	};
}
