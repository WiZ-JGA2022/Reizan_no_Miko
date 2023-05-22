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
		const float m_TotalTimeSeconds = 30.0f;

		shared_ptr<SoundItem> m_BGM;

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
		//�\�z�Ɣj��
		StandbyStage() :Stage() {}
		virtual ~StandbyStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		// �f�o�b�O������\���p
		virtual void OnDraw() override;
	};

}