/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"
#include "TrapUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		const float m_TotalTimeSeconds = 600.0f;

		shared_ptr<SoundItem> m_BGM;
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
		//BGM�̍Đ�
		void PlayBGM();

		// �v���C���[�R���|�[�l���g
		shared_ptr<PlayerController> m_player;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class StandbyStage : public Stage {
		const float m_TotalTimeSeconds = 10.0f;

		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬
		void CreateViewLight();
		// ���x���A�b�v�C�x���g�̍쐬
		void CreateLevelUpEvent();
		// ��l���̍쐬
		void CreatePlayer();
		// UI�̍쐬
		void CreateUI();
		//BGM�̍Đ�
		void PlayBGM();

		// �v���C���[�R���|�[�l���g
		shared_ptr<PlayerController> m_player;
		shared_ptr<TrapSprite> m_trap;

	public:
		//�\�z�Ɣj��
		StandbyStage() :Stage() {}
		virtual ~StandbyStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������
	};

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
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
		TitleStage() :Stage() {}
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

	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateResultSprite();
		//BGM�̍Đ�
		void PlayBGM();

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

		virtual void OnDestroy() override;
		//A�{�^��
		void OnPushA() {
			//�������Ȃ�
		}
		//B�{�^��
		void OnPushB();

	};

}
//end basecross

