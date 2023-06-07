/*!
@file SpikeDrawingProcess.h
@brief �X�p�C�N�̕`�揈���Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpikeModel : public GameObject {
		Vec3 m_position; // �ʒu

	public :
		// �R���X�g���N�^
		SpikeModel(const shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{
		}
		// �f�X�g���N�^
		~SpikeModel() {}

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};

}
