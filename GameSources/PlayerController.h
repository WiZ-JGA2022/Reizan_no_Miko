/*!
@file PlayerController.h
@brief �v���C���[�L����
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class PlayerController : public GameObject
	{
		// �v���C���[�̑���Ɏg�p����{�^��
		const WORD BUTTON_HOMING = XINPUT_GAMEPAD_LEFT_SHOULDER;
		const WORD BUTTON_BARRIER = XINPUT_GAMEPAD_RIGHT_SHOULDER;

		//���̓n���h���[
		InputHandler<PlayerController> m_InputHandler;

	public:
		PlayerController(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V
		
		//X�{�^��
		void OnPushX();
		//void MovePlayer();
		//virtual void OnCollisionEnter(const CollisionPair& Pair) override;
		void DestroyPlayer();
	};
}
