/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, false, true);
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, false, false);
		m_bar[0]->UpdateGaugeSize(m_maxExp, playerStatus->GetStatusValue(L"EXP"));
		m_bar[1]->UpdateGaugeSize(m_maxExp, playerStatus->GetStatusValue(L"EXP"));
		m_bar[0]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // 画面の左端から右端に向かってゲージを伸ばす
		m_bar[1]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // 画面の左端から右端に向かってゲージを伸ばす
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
		m_bar[0]->UpdateGaugeSize(m_maxExp, playerStatus->GetStatusValue(L"EXP"));
		m_bar[1]->UpdateGaugeSize(m_maxExp, (float)m_maxExp);
	}

	void ExpBar::OnDraw()
	{
		m_bar[1]->GameObject::OnDraw();
		m_bar[0]->GameObject::OnDraw();
	}
}
//end basecross
