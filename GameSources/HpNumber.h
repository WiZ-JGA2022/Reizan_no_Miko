/**
@file HpNumber.h
@brief Œ»İHP‚ÆÅ‘åHP‚ğ”š‚Å•\¦‚·‚éUI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class HpNumber : public GameObject {
		
		const Vec2 m_Size = Vec2(12.0f, 24.0f);
		
		int m_place;

		float m_maxHp;

		vector<shared_ptr<NumberUI>> m_numbers;

	public :
		HpNumber(const shared_ptr<Stage>& stage);
		~HpNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int maxHp, float currentHp);
	};
}