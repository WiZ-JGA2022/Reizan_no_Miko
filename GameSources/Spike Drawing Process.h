/*!
@file SpikeDrawingProcess.h
@brief スパイクの描画処理など
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
