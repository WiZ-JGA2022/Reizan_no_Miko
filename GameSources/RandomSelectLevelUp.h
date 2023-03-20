/*!
@file RandomSelectLevelUp.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUp : public GameObject
	{
		Vec3 m_Scale;					//!�傫��
		Vec3 m_Rotation;				//!�p�x
		Vec3 m_Position;				//!�ʒu

		int m_CommandCount = 0;		//!�R�}���h�̉�
		vector<int> m_CommandNums;	//!�{�^���̂̐�����ۑ����Ă����p

		bool m_CommandFlg = true;		//!
		bool m_CreateStateFlg = false;	//!
		int m_PlayCommandCount = 1;		//!
		bool ControllerSprite = true;

		/**
		* A�`X�{�^���A�㉺���E�{�^���Ɋ��蓖�Ă��Ă��鐔���������_���ɐݒ�
		*
		* @param �Ȃ�
		*
		* @return commandnum : 0x0000�Ŋ��蓖�Ă��Ă���pad�̃{�^���̐������
		*/
		int CommandNum();
		/**
		* �R�}���h�̉񐔂��w��
		*
		* @param �Ȃ�
		*
		* @return commandnum : 0x0000�Ŋ��蓖�Ă��Ă���pad�̃{�^���̐������
		*/
		void CommandCount(int maxC);

	public :
		RandomSelectLevelUp(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return ControllerSprite;
		}

		virtual ~RandomSelectLevelUp();

		virtual void OnCreate() override;
	};

}
//end basecross
