/*!
@file PlayerController.h
@brief �v���C���[�L����
@prod ��I�t
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class PlayerController : public GameObject
	{
		// �v���C���[�̏��
		enum class PlayerCondition {
			Standby,
			Play
		};

		// �v���C���[�̍s��
		enum class PlayerAction {
			Wait,
			Walk,
			Attack,
			Damage,
			Died
		};

		// �u����㩂̐�
		enum class TrapLimit {
			SpikeTrap = 5,
			SpurtLava = 1
		};

		PlayerCondition m_condition = PlayerCondition::Standby; // ���

		PlayerAction m_action = PlayerAction::Wait; // �s��

		// 㩂̐�
		TrapLimit m_trapLimit[2] = {
			TrapLimit::SpikeTrap,
			TrapLimit::SpurtLava
		};

		// �v���C���[�̑���Ɏg�p����{�^��
		const WORD BUTTON_SHOT = XINPUT_GAMEPAD_X;
		
		const float m_RecastCount; // �e���ˊԊu

		int m_trapCount[2] = { 0 }; // 㩂̐�

		float m_recastFlame; // ���ˊԊu

		Vec3 m_position; // �ʒu
		Quat m_quaternion; // ��]

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g
	public:
		// �R���X�g���N�^
		PlayerController(const shared_ptr<Stage>& stage, const int condition);
		PlayerController(const shared_ptr<Stage>& stage, const Vec3& position, const Quat& quaternion, const int condition);
		// �f�X�g���N�^
		~PlayerController();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����
		
		/**
		* �v���C���[�̈ړ�����
		*/
		void PlayerMoveProcess();

		/**
		* �v���C���[�̏�Ԃ��擾
		* 
		* @return m_condition ���
		*/ 
		int GetCondition()
		{
			return (int)m_condition;
		}
		
		// 㩂̐ݒu������擾
		int GetTrapLimit(int index)
		{
			return (int)m_trapLimit[index];
		}

		// �ݒu����Ă���㩂̐�
		int GetTrapCount(int index)
		{
			return m_trapCount[index];
		}
	};
}
