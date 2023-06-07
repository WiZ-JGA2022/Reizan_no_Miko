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
		static const int m_PickUpStatusCount = 2;

		bool m_isActiveSprite = false;

	public:
		ButtonSelect(const shared_ptr<Stage>& StagePtr);
		~ButtonSelect();

		virtual void OnCreate() override;
	};
}
//end basecross


