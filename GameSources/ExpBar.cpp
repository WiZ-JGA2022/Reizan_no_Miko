/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	// テスト用
	int currentExp = 0;
	int delay = 120;
	// ここまで

	void ExpBar::OnCreate()
	{
		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(),200.0f, false); // オブジェクトを生成するけどステージに追加しない
		m_bar->UpdateGaugeSize(10.0f, currentExp);
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // 画面の左端から右端に向かってゲージを伸ばす
	}

	// 更新処理 //
	void ExpBar::OnUpdate()
	{
		// テスト用 //
		delay--;
		if (delay < 0)
		{
			currentExp += 1;
			delay = 120;
		}
		// ここまで //

		m_bar->UpdateGaugeSize(10.0f, currentExp);
	}

	// 描画処理 //
	void ExpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
