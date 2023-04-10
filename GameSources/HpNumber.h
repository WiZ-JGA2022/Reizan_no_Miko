/**
@file HpNumber.h
@brief 現在HPと最大HPを数字で表示するUI
*/

#pragma once
#include "stdafx.h"
//#include "NumberUI.h"

namespace basecross {
	class HpNumber : public GameObject {
		
		const Vec2 m_Size = Vec2(12.0f, 24.0f);
		
		int m_place;

		float m_maxHp;

		//vector<shared_ptr<NumberUI>> m_numbers;

	public :
		HpNumber(const shared_ptr<Stage>& stage);
		~HpNumber();

		void OnCreate() override;
		//void OnUpdate() override;
		//void OnDraw() override;

		//void UpdateValue(float Hp, bool isMax);
	};
}