/*!
@file ClearStage.h
@brief �Q�[���N���A���̃X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�N���A�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {
		shared_ptr<SoundItem> m_bgm;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateResultSprite();
		//BGM�̍Đ�
		void PlayBGM();

		//���̓n���h���[
		InputHandler2<ClearStage> m_inputHandler;
	public:
		// �R���X�g���N�^
		ClearStage() :Stage() {}
		// �f�X�g���N�^
		virtual ~ClearStage() {}
		// ������
		virtual void OnCreate()override;
		// �X�V
		virtual void OnUpdate()override;
		// �j�󏈗�
		virtual void OnDestroy() override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();

	};
}
