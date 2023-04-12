/*!
@file ExpBar.cpp
@brief �o���l��\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, false); 
		m_bar->UpdateGaugeSize(m_maxExp, playerStatus->GetStatusValue(L"EXP"));
		m_bar->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	void ExpBar::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		if (m_maxExp < playerStatus->GetMaxExp())
		{
			m_maxExp = playerStatus->GetMaxExp();
		}
		m_bar->UpdateGaugeSize(m_maxExp, playerStatus->GetStatusValue(L"EXP"));
	}

	void ExpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
