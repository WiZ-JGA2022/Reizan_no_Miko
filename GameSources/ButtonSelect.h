/*!
@file ButtonSelect.h
@brief �����̃{�^��UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ButtonSelect : public GameObject
	{
		// ���x���A�b�v���ɕ\������{�^���̐�
		static const int m_PickUpStatusCount = 4;

		int m_spriteNums[m_PickUpStatusCount] = { 0 };	// �{�^���̐�����ۑ����Ă����p

		bool m_isActiveSprite = false;

	public:
		ButtonSelect(const shared_ptr<Stage>& StagePtr);
		~ButtonSelect();

		virtual void OnCreate() override;




		int GetSpriteNums(int index)
		{
			return m_spriteNums[index];
		}
	};
}
//end basecross


