/**
@file TimeNumber.h
@brief 制限時間UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		// 大きさ
		const Vec2 m_NumberSize = Vec2(24.0f, 48.0f);
		const int m_OneMinite = 60;

		int m_place; // 桁数

		float m_totalTime; // 制限時間
		int m_minutes; // 分
		float m_seconds; // 秒
		float m_oldSeconds; // 直前の時間

		bool m_isPlay;
		// 数字
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