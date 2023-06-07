/*!
@file StageCollision.h
@brief �n�ʂ�\���N���X���`����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollision : public GameObject
	{
		Vec3 m_position; // �ʒu
		Vec3 m_scale; // �傫��

	public:
		// �R���X�g���N�^
		StageCollision(const std::shared_ptr<Stage>& stage,const Vec3& potision,const Vec3& scale);
		// �f�X�g���N�^
		~StageCollision();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};
}