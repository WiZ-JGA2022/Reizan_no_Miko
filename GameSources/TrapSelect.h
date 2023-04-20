/*!
@file RandomSelectLevelUpButton.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapSelect : public GameObject
	{
		// ���x���A�b�v���ɕ\������{�^���̐�
		static const int m_PickUpStatusCount = 4;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// �{�^���̐�����ۑ����Ă����p

		bool m_isActiveSprite = false;

		/**
		* �����ł���X�e�[�^�X�E�����ł��镐��������_���Ɏw��
		*
		* @param selectStatus �����\�ȃX�e�[�^�X�E����̑���
		*/

	public:
		TrapSelect(const shared_ptr<Stage>& StagePtr);
		~TrapSelect();

		virtual void OnCreate() override;

		/**
		* ���x���A�b�v���ɌĂ΂��֐�
		*/




		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross
