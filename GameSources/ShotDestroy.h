/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ShotDestroy : public GameObject
	{

	public:
		ShotDestroy(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnUpdate() override; // オブジェクトデータの更新
	};


}
