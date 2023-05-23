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

		enum class PlayerAction {
			Wait,
			Walk,
			Attack,
			Damage,
			Died
		};

		enum class TrapLimit {
			SpikeTrap = 5,
			SpurtLava = 1
		};

		PlayerCondition m_condition = PlayerCondition::Standby;

		PlayerAction m_action = PlayerAction::Wait;

		TrapLimit m_trapLimit[2] = {
			TrapLimit::SpikeTrap,
			TrapLimit::SpurtLava
		};

		// �v���C���[�̑���Ɏg�p����{�^��
		const WORD BUTTON_SHOT = XINPUT_GAMEPAD_X;
		
		const float m_RecastCount;

		int m_trapCount[2] = { 0 };

		int m_spikeTrapCount;
		int m_lavaTrapCount;
		float m_recastFlame;


		Vec3 m_position;
		Quat m_quaternion;

		shared_ptr<Transform> m_transform;
	public:
		PlayerController(const shared_ptr<Stage>& stage, const int condition);
		PlayerController(const shared_ptr<Stage>& stage, const Vec3& position, const Quat& quaternion, const int condition);
		~PlayerController();

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

		int GetTrapLimit(int index)
		{
			return (int)m_trapLimit[index];
		}

		int GetTrapCount(int index)
		{
			return m_trapCount[index];
		}
	};
}
