/*!
@file RandomSelectLevelUpButton.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandomSelectLevelUpButton : public GameObject
	{
		// ���x���A�b�v���ɕ\������{�^���̐�
		static const int m_PickUpStatusCount = 3;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// �{�^���̐�����ۑ����Ă����p

		bool m_isActiveSprite = false;

		/**
		* �����ł���X�e�[�^�X�E�����ł��镐��������_���Ɏw��
		*
		* @param selectStatus �����\�ȃX�e�[�^�X�E����̑���
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr);
		~RandomSelectLevelUpButton();

		virtual void OnCreate() override;

		/**
		* ���x���A�b�v���ɌĂ΂��֐�
		*/
		void LevelUpEvent();

		bool GetEventActive() 
		{
			return m_isActiveSprite;
		}

		void SetEventActive(bool active)
		{
			m_isActiveSprite = active;
		}

		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross
