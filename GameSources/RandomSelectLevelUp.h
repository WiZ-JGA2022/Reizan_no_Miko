/*!
@file RandomSelectLevelUp.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUp : public GameObject
	{
		Vec3 m_Scale;					// �傫��
		Vec3 m_Rotation;				// �p�x
		Vec3 m_Position;				// �ʒu

		// ���x���A�b�v���ɕ\������{�^���̐�
		static const int m_PickUpStatusCount = 3;

		int m_CommandCount = 0;		// �R�}���h�̉�
		int m_CommandNums[m_PickUpStatusCount] = { 0 };	// �{�^���̂̐�����ۑ����Ă����p

		bool m_CommandFlg = true;		
		bool m_CreateStateFlg = false;	
		bool ControllerSprite = true;

		/**
		* �����ł���X�e�[�^�X�E�����ł��镐��������_���Ɏw��
		*
		* @param selectStatus �����\�ȃX�e�[�^�X�E����̑���
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUp(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return ControllerSprite;
		}

		virtual ~RandomSelectLevelUp();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
