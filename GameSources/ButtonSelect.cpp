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

	void ButtonSelect::OnCreate()
	{

		/*auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"LEVELUP_SE", 0, 0.1f);*/

		for (int i = 0; i < m_PickUpStatusCount; i++)
		{
			GetStage()->AddGameObject<ButtonSprite>(i, true, Vec2(100.0f, 100.0f), Vec2(-500.0f + (i * 250.0f) + (i * 20), -250.0f), i);
		}
	} // end OnCreate



}
