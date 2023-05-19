/* !
@file RBButtonUI.h
@brief RBButtonUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class RBButtonSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		RBButtonSprite(const shared_ptr<Stage>& stage);
		~RBButtonSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}

