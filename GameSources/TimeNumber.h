/**
@file TimeNumber.h
@brief 現在EXPと最大EXPを数字で表示するUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place; // 桁数

		float m_totalTime;
		int m_minutes; // 分
		float m_seconds; // 秒
		float m_oldSeconds;


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