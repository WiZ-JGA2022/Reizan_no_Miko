/*!
@file DefeatStage.h
@brief �Q�[�����s���̃X�e�[�W
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class DefeatStage : public Stage {
		shared_ptr<SoundItem> m_bgm;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateResultSprite();
		//BGM�̍Đ�
		void PlayBGM();

		//���̓n���h���[
		InputHandler2<DefeatStage> m_inputHandler;
	public:
		// �R���X�g���N�^
		DefeatStage() :Stage() {}
		// �f�X�g���N�^
		virtual ~DefeatStage() {}

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