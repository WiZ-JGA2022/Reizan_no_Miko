/* !
@file ResultSprite.h
@brief リザルトシーンの背景
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class ResultSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		ResultSprite(const shared_ptr<Stage>& stage);
		~ResultSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};

	class ClearSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		ClearSprite(const shared_ptr<Stage>& stage);
		~ClearSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}