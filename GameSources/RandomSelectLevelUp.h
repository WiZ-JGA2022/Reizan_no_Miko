/*!
@file RandomSelectLevelUpButton.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUpButton : public GameObject
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
		bool m_ControllerSprite = true;

		/**
		* �����ł���X�e�[�^�X�E�����ł��镐��������_���Ɏw��
		*
		* @param selectStatus �����\�ȃX�e�[�^�X�E����̑���
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return m_ControllerSprite;
		}

		virtual ~RandomSelectLevelUpButton();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void LevelUpEvent();
	};

}
//end basecross
