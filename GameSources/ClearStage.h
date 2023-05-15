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
		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateResultSprite();
		//BGM�̍Đ�
		void PlayBGM();

		//���̓n���h���[
		InputHandler2<ClearStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

		virtual void OnDestroy() override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();

	};
}
