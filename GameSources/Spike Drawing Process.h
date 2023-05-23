/*!
@file SpikeDrawingProcess.h
@brief �X�p�C�N�̕`�揈���Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpikeModel : public GameObject {
		Vec3 m_position;

	public :
		SpikeModel(const shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{
		}
		~SpikeModel() {}

		void OnCreate() override;
		void OnUpdate() override;
	};

}
