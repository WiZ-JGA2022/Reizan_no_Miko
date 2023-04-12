/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		// �G�̍쐬
		void CreateEnemy();
		// ���x���A�b�v�C�x���g�̍쐬
		void CreateLevelUpEvent();
		// ��l���̍쐬
		void CreatePlayer();
		// UI�̍쐬
		void CreateUI();

		// �v���C���[�R���|�[�l���g
		shared_ptr<PlayerController> m_player;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������
	};

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//���̓n���h���[
		InputHandler2<TitleStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();

	};

	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//���̓n���h���[
		InputHandler2<ResultStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();

	};

}
//end basecross

