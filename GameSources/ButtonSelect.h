/*!
@file ButtonSelect.h
@brief �����̃{�^��UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ButtonSelect : public GameObject
	{	
		static const int m_PickUpStatusCount = 2; // �\������{�^���̐�

		bool m_isActiveSprite = false;

	public:
		//�R���X�g���N�^
		ButtonSelect(const shared_ptr<Stage>& StagePtr);
		//�f�X�g���N�^
		~ButtonSelect();

	
		//������
		virtual void OnCreate() override;
	};
}
//end basecross


