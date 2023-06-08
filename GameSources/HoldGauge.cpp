/*!
@file HoldGauge.cpp
@brief 長押しバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void HoldBar::OnCreate()
	{
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");		//位置座標、ソース画像
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBARFRAME");	//位置座標、ソース画像
		m_bar[0]->UpdateGaugeSize(m_maxTime,(float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
		m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	//更新処理
	void HoldBar::OnUpdate()
	{
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");	//TimeNumberの取得
		m_bar[0]->UpdateGaugeSize(m_maxTime, (float)time->GetSkipTime());	//ゲージの上限
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);				//ゲージの上限
	}

	//描画処理
	void HoldBar::OnDraw()
	{
		m_bar[0]->GameObject::OnDraw();
		m_bar[1]->GameObject::OnDraw();

	}
}
//end basecross
