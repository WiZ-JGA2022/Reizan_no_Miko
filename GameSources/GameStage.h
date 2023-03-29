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

		void CreatePlayer();

		shared_ptr<PlayerController> m_player;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		void CreateItem();
		//������
		virtual void OnCreate() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������


	};


}
//end basecross

