/**
@file TimeNumber.h
@brief ��������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {

		const WORD BUTTON_TIMESKIP = XINPUT_GAMEPAD_RIGHT_SHOULDER;

		// �傫��
		const Vec2 m_NumberSize;
		const int m_OneMinite;

		int m_place; // ����

		float m_totalTime; // ��������
		int m_minutes; // ��
		float m_seconds; // �b
		float m_oldSeconds; // ���O�̎���

		float m_timeSkip;
		bool m_skipFlag;

		bool m_isPlay;
		// ����
		vector<shared_ptr<NumberUI>> m_numbers;

	public:
		TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay, const bool skipFlag);
		~TimeNumber();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void UpdateValue(int minites, float seconds);
		float GetTimeLeft();
		float GetSkipTime()
		{
			return m_timeSkip;
		}

	};
}