/*!
@file RandomSelectLevelUpButton.cpp
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X�̎���
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

		/*auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"LEVELUP_SE", 0, 0.1f);*/

		for (int i = 0; i < m_PickUpStatusCount; i++)
		{
			GetStage()->AddGameObject<TrapSprite>(i, true, Vec2(100.0f, 100.0f), Vec2(-390.0f + (i * 250.0f) + (i * 20), -250.0f), i);
		}
	} // end OnCreate



}
