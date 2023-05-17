/**
@file CountDownNumber.h
@brief カウントダウンUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class CountDownNumber : public Sprites {
		const Vec2 m_DefaultSize;
		const Vec3 m_DefaultPosition;

	public :
		CountDownNumber(const shared_ptr<Stage>& stage);
		~CountDownNumber();

		void OnCreate() override;
		void OnUpdate() override;
	};
}