/*!
@file TrapSelect.cpp
@brief �g���b�v��A���ŕ\��������N���X�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	TrapSelect::TrapSelect(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end �R���X�g���N�^

	TrapSelect::~TrapSelect() {}
	// end �f�X�g���N�^

	void TrapSelect::OnCreate()
	{
		for (int i = 0; i < m_PickUpStatusCount; i++) //for���ŘA���ŕ\��������摜�̈ʒu���W�̏���
		{
			GetStage()->AddGameObject<TrapSprite>(i, true, Vec2(75.0f, 75.0f), Vec2(-400.0f + (i * 250.0f) + (i * 20), -300.0f), i);
		}
	} // end OnCreate



}
