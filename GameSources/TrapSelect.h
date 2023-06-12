/*!
@file TrapSelect.h
@brief �g���b�v��I��UI
@prod ��I�t
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
