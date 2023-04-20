/*!
@file PlayerController.h
@brief �v���C���[�L����
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class PlayerController : public GameObject
	{
		enum class PlayerCondition {
			Standby,
			Play
		};

		enum class TrapLimit {
			SpikeTrap = 5,
			SpurtLava = 1
		};

		PlayerCondition m_condition = PlayerCondition::Standby;

		// �v���C���[�̑���Ɏg�p����{�^��
		const WORD BUTTON_HOMING = XINPUT_GAMEPAD_LEFT_SHOULDER;
		const WORD BUTTON_BARRIER = XINPUT_GAMEPAD_RIGHT_SHOULDER;
		const WORD BUTTON_SHOT = XINPUT_GAMEPAD_X;
		
		const float m_RecastCount;

		int m_spikeTrapCount;
		int m_lavaTrapCount;
		float m_recastFlame;

		shared_ptr<Transform> m_transform;
	public:
		PlayerController(const std::shared_ptr<Stage>& stage, const int condition) :
			GameObject(stage),
			m_RecastCount(9.0f),
			m_spikeTrapCount(0),
			m_lavaTrapCount(0),
			m_condition((PlayerCondition)condition),
			m_recastFlame(m_RecastCount)
		{
		}
		~PlayerController() {}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V
		
		/**
		* �v���C���[�̈ړ�����
		*/
		void PlayerMoveProcess();

		int GetCondition()
		{
			return (int)m_condition;
		}
		void SetCondition(int conditionIndex)
		{
			m_condition = (PlayerCondition)conditionIndex;
		}
	};
}
