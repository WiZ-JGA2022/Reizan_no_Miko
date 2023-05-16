/**
@file StandbySprite.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StandbySprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		StandbySprite(const shared_ptr<Stage>& stage);
		~StandbySprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}