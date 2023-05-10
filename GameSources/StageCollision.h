/*!
@file StageCollision.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollision : public GameObject
	{
	public:
		StageCollision(const std::shared_ptr<Stage>& stage);
		~StageCollision();

		void OnCreate() override;
		void OnUpdate() override;
	};
}