/**
@file TimeNumber.h
@brief ��������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {
		// �X�L�b�v�{�^��
		const WORD BUTTON_TIMESKIP = XINPUT_GAMEPAD_RIGHT_SHOULDER;
				
		const Vec2 m_NumberSize; // �傫��
		const int m_OneMinite; // �ꕪ

		int m_place; // ����

		float m_totalTime; // ��������
		int m_minutes; // ��
		float m_seconds; // �b
		float m_oldSeconds; // ���O�̎���

		float m_timeSkip; // �c�莞�Ԃ̃X�L�b�v
		bool m_skipFlag; // �X�L�b�v�̃t���O

		bool m_isPlay; // 
		bool m_startCountDown; // �J�E���g�_�E��
		
		vector<shared_ptr<NumberUI>> m_numbers; // ����
		shared_ptr<SoundItem> m_se; // se�p

	public:
		// �R���X�g���N�^
		TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay, const bool skipFlag);
		// �f�X�g���N�^
		~TimeNumber();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
		// �`�揈��
		void OnDraw() override;

		void UpdateValue(int minites, float seconds);
		float GetTimeLeft();
		float GetSkipTime()
		{
			return m_timeSkip;
		}

	};
}