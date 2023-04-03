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
		// �e�X�g�p
		void CreateItem();

		// �G�̍쐬
		void CreateEnemy();

		// ���x���A�b�v�C�x���g�̍쐬
		void CreateLevelUpEvent();

		// ��l���̍쐬
		void CreatePlayer();

		// �v���C���[�R���|�[�l���g
		shared_ptr<PlayerController> m_player;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������


	};


}
//end basecross

