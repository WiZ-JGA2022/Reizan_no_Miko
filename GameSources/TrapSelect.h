/*!
@file RandomSelectLevelUpButton.h
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapSelect : public GameObject
	{
		static const int m_PickUpStatusCount = 2;// �\������g���b�v�̐�

	public:
		// �R���X�g���N�^
		TrapSelect(const shared_ptr<Stage>& StagePtr);
		// �f�X�g���N�^
		~TrapSelect();

		//������
		virtual void OnCreate() override;
	};
}
//end basecross
