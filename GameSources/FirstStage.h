/*!
@file FirstStage.h
@brief ���t�F�[�Y�X�e�[�W
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
		const float m_TotalTimeSeconds = 240.0f;
		bool m_isOnce = true;

		shared_ptr<SoundItem> m_BGM;
		//�r���[�̍쐬
		void CreateViewLight();
		// �G�̍쐬
		void CreateEnemy();
		// ��l���̍쐬
		void CreatePlayer();
		// UI�̍쐬
		void CreateUI();
		// �G�t�F�N�g�R���g���[���[�̍쐬
		void CreateEffectController();
		//BGM�̍Đ�
		void PlayBGM();

		// �e��R���|�[�l���g
		shared_ptr<PlayerController> m_player;

	public:
		//�\�z�Ɣj��
		FirstStage() :Stage() {}
		virtual ~FirstStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������

	};


}
//end basecross

