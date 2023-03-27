/*!
@file HpBar.cpp
@brief プレイヤーの体力を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true); // オブジェクトを生成するけどステージに追加しない
		m_bar->UpdateGaugeSize(30.0f, 30.0f);
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	void HpBar::OnUpdate()
	{
		m_bar->UpdateGaugeSize(30.0f, 30.0f);
	}

	void HpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
