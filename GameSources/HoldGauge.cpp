/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HoldBar::OnCreate()
	{
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBARFRAME");
		m_bar[0]->UpdateGaugeSize(m_maxTime,(float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
		m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	void HoldBar::OnUpdate()
	{
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");
		m_bar[0]->UpdateGaugeSize(m_maxTime, (float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
	}

	void HoldBar::OnDraw()
	{
		m_bar[0]->GameObject::OnDraw();
		m_bar[1]->GameObject::OnDraw();

	}
}
//end basecross
