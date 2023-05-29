/*!
@file RightStick.h
@brief 耐久値スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class RightStick : public Sprites {
		const Vec2 m_DefaultSize;

		wstring m_texKey;

	public:
		RightStick(const shared_ptr<Stage>& stage);
		~RightStick();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
