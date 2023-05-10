/*!
@file StageCollision.h
@brief �n�ʂ�\���N���X���`����
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