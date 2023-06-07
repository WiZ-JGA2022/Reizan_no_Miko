/*!
@file StandbyStage.h
@brief �����t�F�[�Y�X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "ProjectBehavior.h"
#include "PlayerController.h"

namespace basecross {
	class StandbyStage : public Stage {
		const float m_TotalTimeSeconds = 30.0f; // ��������

		shared_ptr<SoundItem> m_bgm;

		//�r���[�̍쐬
		void CreateViewLight();
		// ��l���̍쐬
		void CreatePlayer();
		// UI�̍쐬
		void CreateUI();
		//BGM�̍Đ�
		void PlayBGM();

		// �v���C���[�R���|�[�l���g
		shared_ptr<PlayerController> m_player;

	public:
		// �R���X�g���N�^
		StandbyStage() :Stage() {}
		// �f�X�g���N�^
		virtual ~StandbyStage() {}

		//������
		virtual void OnCreate() override;
		// �X�V����
		virtual void OnUpdate() override;
		// �j������
		virtual void OnDestroy() override;
		// �`�揈��
		virtual void OnDraw() override;

		// �X�e�[�W�ύX����
		void ChangeStage();
	};

}