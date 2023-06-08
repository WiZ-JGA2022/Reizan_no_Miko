/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HoldBar::OnCreate()
	{
		// timeNumberオブジェクトを取得
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		// ゲージを生成
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBARFRAME");
		// ゲージの大きさを設定
		m_bar[0]->UpdateGaugeSize(m_maxTime,(float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
		// 画面の右上に表示
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); 
		m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f);
	}

	void HoldBar::OnUpdate()
	{
		// ゲージサイズの更新
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");
		m_bar[0]->UpdateGaugeSize(m_maxTime, (float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
	}

	void HoldBar::OnDraw()
	{
		// ゲージの描画
		m_bar[0]->GameObject::OnDraw();
		m_bar[1]->GameObject::OnDraw();
	}
}
//end basecross
