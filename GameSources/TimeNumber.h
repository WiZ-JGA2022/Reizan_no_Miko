/**
@file TimeNumber.h
@brief §ŒÀŠÔUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		// ‘å‚«‚³
		const Vec2 m_NumberSize;
		const int m_OneMinite;

		int m_place; // Œ…”

		float m_totalTime; // §ŒÀŠÔ
		int m_minutes; // •ª
		float m_seconds; // •b
		float m_oldSeconds; // ’¼‘O‚ÌŠÔ

		bool m_isPlay;
		// ”š
		vector<shared_ptr<NumberUI>> m_numbers;

	public:
		TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay);
		~TimeNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int minites, float seconds);
		float GetTimeLeft();
	};
}