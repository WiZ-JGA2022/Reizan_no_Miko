/*!
@file HpBar.cpp
@brief プレイヤーの体力を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true);
		m_bar->UpdateGaugeSize(playerStatus->GetMaxHp(), playerStatus->GetStatusValue(L"HP"));
		m_bar->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	void HpBar::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		m_bar->UpdateGaugeSize(playerStatus->GetMaxHp(), playerStatus->GetStatusValue(L"HP"));
	}

	void HpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
