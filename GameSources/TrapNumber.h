/**
@file HpNumber.h
@brief Œ»İHP‚ÆÅ‘åHP‚ğ”š‚Å•\¦‚·‚éUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TrapNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place;

		float m_maxHp;

		vector<shared_ptr<NumberUI>> m_numbers[4];

	public:
		TrapNumber(const shared_ptr<Stage>& stage);
		~TrapNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int trapLimit, int currentTrapCount, int index);
	};
}
