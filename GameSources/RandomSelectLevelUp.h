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

		bool m_isActiveSprite = true;

		/**
		* �����ł���X�e�[�^�X�E�����ł��镐��������_���Ɏw��
		*
		* @param selectStatus �����\�ȃX�e�[�^�X�E����̑���
		*/
		void RandomSelect(int selectStatus);

	public :
		RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr);

		bool GetControllerSprite() {
			return m_isActiveSprite;
		}

		virtual ~RandomSelectLevelUpButton();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void LevelUpEvent();
	};

}
//end basecross
