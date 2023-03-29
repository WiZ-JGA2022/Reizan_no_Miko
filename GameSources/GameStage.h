/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�ǂ�������I�u�W�F�N�g�̍쐬
		void CreateSeekObject();
		//�v���C���[�̍쐬
		void CreatePlayer();


	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//�v���C���[�̍쐬
		void CreatePlayer();
		void CreateItem();
		//������
		virtual void OnCreate() override;

		virtual void OnDraw() override; // �f�o�b�O�����p�ɏ㏑������


	};


}
//end basecross

