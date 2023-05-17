/**
@file TimeChara.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TimeChara : public Sprites {
		const Vec2 m_DefaultSize;

	public :
		TimeChara(const shared_ptr<Stage>& stage);
		~TimeChara();

		void OnCreate() override;
		void OnUpdate() override;

	};
}