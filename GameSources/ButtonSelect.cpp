/*!
@file ButtonSelect.cpp
@brief �{�^��UI�𕡐�����
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	ButtonSelect::ButtonSelect(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end �R���X�g���N�^

	ButtonSelect::~ButtonSelect() {}
	// end �f�X�g���N�^

	// ������
	void ButtonSelect::OnCreate()
	{
		// ButtonSprite�̐���
		for (int i = 0; i < m_PickUpStatusCount; i++)
		{
			GetStage()->AddGameObject<ButtonSprite>(i, true, Vec2(75.0f, 75.0f), Vec2(-500.0f + (i * 250.0f) + (i * 20), -300.0f), i);	//�A���ŕ\�����镡���̉摜�̈ʒu���W�̐ݒ�
		}
	} // end OnCreate



}
