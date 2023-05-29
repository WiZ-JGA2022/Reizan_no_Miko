/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_BGM;

		bool m_start;

		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();

		//BGM�̍Đ�
		void PlayBGM();
		//���̓n���h���[
		InputHandler2<TitleStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		TitleStage() :
			Stage(),
			m_start(false)
		{}
		virtual ~TitleStage() {}
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