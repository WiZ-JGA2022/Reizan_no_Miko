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
		const WORD BUTTON_SHOT = XINPUT_GAMEPAD_X;
		
		const float m_RecastCount;
		float m_recastFlame;

		shared_ptr<Transform> m_transform;

	public:
		PlayerController(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_RecastCount(9.0f),
			m_recastFlame(m_RecastCount)
		{
		}
		~PlayerController() {}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V
		
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;
	};
}
