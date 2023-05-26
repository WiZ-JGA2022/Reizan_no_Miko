/*!
@file KeyStoneHpGauge.cpp
@brief 要石の体力を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");

		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_GREEN");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_RED");
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());
		m_bar[0]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // 画面の左端から右端に向かってゲージを伸ばす
		m_bar[1]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	void HpBar::OnUpdate()
	{
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());
	}

	void HpBar::OnDraw()
	{
		m_bar[1]->GameObject::OnDraw();
		m_bar[0]->GameObject::OnDraw();
	}
}
//end basecross
