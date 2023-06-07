/*!
@file TrapController.h
@brief 㩂��Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapController : public GameObject {
		
		// 㩂̏��
		enum class TrapState
		{
			Wait,		// �ҋ@
			Active,		// ���s
			ActiveDelay	// ���s�x��
		};
		enum TrapState m_isState = TrapState::Wait;

		const int m_TrapActiveDelaySeconds = 180; // �g���b�v�����s��ԂɂȂ�܂ł̒x��
		const int m_TrapDamageDelayFlame = 180; // �g���b�v���_���[�W��^����Ԋu

		int m_trapDamageDelay; 

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

	public :
		// �R���X�g���N�^
		TrapController(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~TrapController();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

		// �n��㩂̍쐬
		void CreateSpurtLava();

	};
}
