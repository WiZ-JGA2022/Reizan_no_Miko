/**
@file GameSprite.h
@brief •¶Žš‚Ì•\Ž¦
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class GameSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		GameSprite(const shared_ptr<Stage>& stage);
		~GameSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}