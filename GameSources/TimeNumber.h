/**
@file TimeNumber.h
@brief Œ»İEXP‚ÆÅ‘åEXP‚ğ”š‚Å•\¦‚·‚éUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		// ‘å‚«‚³
		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place; // Œ…”

		float m_totalTime; // §ŒÀŠÔ
		int m_minutes; // •ª
		float m_seconds; // •b
		float m_oldSeconds; // ’¼‘O‚ÌŠÔ

		// ”š
		vector<shared_ptr<NumberUI>> m_numbers;

	public:
		TimeNumber(const shared_ptr<Stage>& stage);
		~TimeNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int minites, float seconds);
	};
}