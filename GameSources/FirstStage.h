/*!
@file FirstStage.h
@brief ���t�F�[�Y�X�e�[�W
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"
#include "EfkInterface.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class FirstStage : public Stage {
		const float m_TotalTimeSeconds = 120.0f; // ��������

		bool m_isChangeStage;

		shared_ptr<SoundItem> m_bgm; // �T�E���h�A�C�e��
		shared_ptr<PlayerController> m_player; // �v���C���[�R���|�[�l���g

		//�r���[�̍쐬
		void CreateViewLight();
		// �G�̍쐬
		void CreateEnemy();
		// ��l���̍쐬
		void CreatePlayer();
		// UI�̍쐬
		void CreateUI();
		//BGM�̍Đ�
		void PlayBGM();

	public:
		// �R���X�g���N�^
		FirstStage() :
			Stage(),
			m_isChangeStage(false)
		{}
		// �f�X�g���N�^
		virtual ~FirstStage() {}

		//������
		virtual void OnCreate() override;
		// �X�V����
		virtual void OnUpdate() override;
		// �j�󏈗�
		virtual void OnDestroy() override;
		// �`�揈��
		virtual void OnDraw() override; 

		bool GetChangingStage()
		{
			return m_isChangeStage;
		}
	};
}
//end basecross

