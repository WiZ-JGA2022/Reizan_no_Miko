/* !
@file KeyStoneHpGauge.h
@brief 要石の体力を表示するバー
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"
#include <vector>

namespace basecross {

	class HpBar : public GameObject
	{
		// 最大HP
		float m_maxHP;

		// HPバーの情報を入れる変数
		shared_ptr<GaugeSizeSettings> m_bar[2];
	public:
		// コンストラクタ
		HpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxHP(0)
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

