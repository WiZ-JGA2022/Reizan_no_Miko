/* !
@file HoldSkip.h
@brief HoldSkip
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class HoldSkipSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		HoldSkipSprite(const shared_ptr<Stage>& stage);
		~HoldSkipSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}
