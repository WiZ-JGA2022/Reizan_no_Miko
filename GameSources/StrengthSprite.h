/*!
@file StrengthSprite.h
@brief 耐久値スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class StrengthSprite : public Sprites {
		const Vec2 m_DefaultSize;

		wstring m_texKey;

	public:
		StrengthSprite(const shared_ptr<Stage>& stage);
		~StrengthSprite();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
