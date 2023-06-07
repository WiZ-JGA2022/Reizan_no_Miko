/**
* @file HoldGauge.h
* @brief スキップボタン長押し中に増えるゲージ
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"

namespace basecross {

	class HoldBar : public GameObject
	{
		int m_maxTime; // 最大時間

		shared_ptr<GaugeSizeSettings> m_bar[2];// バーの情報を入れる変数

	public:
		// コンストラクタ
		HoldBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxTime(3)
		{
		}

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
		// 描画処理
		void OnDraw() override;
	};
}
//end basecross

