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

		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true); // オブジェクトを生成するけどステージに追加しない
		m_bar->UpdateGaugeSize(playerStatus->GetStatusValue(L"HP"), playerStatus->GetStatusValue(L"HP"));
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	void HpBar::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		if (m_maxHP < playerStatus->GetStatusValue(L"HP"))
		{
			m_maxHP = playerStatus->GetStatusValue(L"HP");
		}
		m_bar->UpdateGaugeSize(m_maxHP, playerStatus->GetStatusValue(L"HP"));
	}

	void HpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
