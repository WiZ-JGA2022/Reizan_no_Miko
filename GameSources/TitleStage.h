/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_bgm; // �T�E���h�A�C�e��

		bool m_start; // �X�^�[�g�{�^���������ꂽ��

		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();

		//BGM�̍Đ�
		void PlayBGM();
		//���̓n���h���[
		InputHandler2<TitleStage> m_inputHandler;
	public:
		// �R���X�g���N�^
		TitleStage() :
			Stage(),
			m_start(false)
		{}
		// �f�X�g���N�^
		virtual ~TitleStage() {}

		// ������
		virtual void OnCreate()override;
		// �X�V
		virtual void OnUpdate()override;
		// �j�󏈗�
		virtual void OnDestroy() override;
		// A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		// B�{�^��
		void OnPushB();

	};

}