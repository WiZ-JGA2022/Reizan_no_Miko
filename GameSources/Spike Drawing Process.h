/*!
@file SpikeDrawingProcess.h
@brief スパイクの描画処理など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpikeModel : public GameObject {
		Vec3 m_position; // 位置

	public :
		// コンストラクタ
		SpikeModel(const shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{
		}
		// デストラクタ
		~SpikeModel() {}

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
	};

}
