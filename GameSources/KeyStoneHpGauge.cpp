/*!
@file KeyStoneHpGauge.cpp
@brief 要石の体力を表示するバーの実装
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		// KeyStoneオブジェクトの取得
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");

		// ゲージの生成
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_GREEN");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_RED");

		// ゲージサイズの設定
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());

		// 画面の左上に表示
		m_bar[0]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); 
		m_bar[1]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); 
	}

	void HpBar::OnUpdate()
	{
		// ゲージサイズの更新
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());
	}

	void HpBar::OnDraw()
	{
		// ゲージの描画
		m_bar[1]->GameObject::OnDraw();
		m_bar[0]->GameObject::OnDraw();
	}
}
//end basecross
