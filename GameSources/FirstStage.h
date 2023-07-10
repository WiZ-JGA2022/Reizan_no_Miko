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

		bool m_isChangeStage; // �X�e�[�W�ύX�t���O

		shared_ptr<SoundItem> m_bgm; // �T�E���h�A�C�e��

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

		/**
		* @brief �X�e�[�W���ύX����Ă��邩�ǂ����擾����֐�
		* @return true�Ȃ�X�e�[�W�ύX�� false�Ȃ�X�e�[�W�ύX����Ă��Ȃ�
		*/
		bool GetChangingStage()
		{
			return m_isChangeStage;
		}
	};
}
//end basecross

