/**
@file GameSprite.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class GameSprite : public Sprites {
		const Vec2 m_DefaultSize;
		const Vec2 m_AfterSize;

	public:
		GameSprite(const shared_ptr<Stage>& stage);
		~GameSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}