/**
@file TimeNumber.h
@brief ����EXP�ƍő�EXP�𐔎��ŕ\������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		// �傫��
		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place; // ����

		float m_totalTime; // ��������
		int m_minutes; // ��
		float m_seconds; // �b
		float m_oldSeconds; // ���O�̎���

		// ����
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