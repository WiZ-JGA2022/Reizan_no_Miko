/**
@file ExpNumber.h
@brief Œ»İEXP‚ÆÅ‘åEXP‚ğ”š‚Å•\¦‚·‚éUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class ExpNumber : public GameObject {

		const Vec2 m_Size = Vec2(12.0f, 24.0f);

		int m_place;

		float m_maxExp;

		vector<shared_ptr<NumberUI>> m_numbers;

	public:
		ExpNumber(const shared_ptr<Stage>& stage);
		~ExpNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int maxExp, float currentHp);
	};
}