/*!
@file SpurtLava.h
@brief ���o����n��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpurtLava : public GameObject {

		Vec3 m_position; // ���̃I�u�W�F�N�g�̈ʒu���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public:
		SpurtLava(const shared_ptr<Stage>& stage);
		SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;

		// �Փˉ�������
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};
}
