/**
@file TimeNumber.h
@brief ��������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		// �傫��
		const Vec2 m_NumberSize = Vec2(24.0f, 48.0f);
		const int m_OneMinite = 60;

		int m_place; // ����

		float m_totalTime; // ��������
		int m_minutes; // ��
		float m_seconds; // �b
		float m_oldSeconds; // ���O�̎���

		bool m_isPlay;
		// ����
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