/* !
@file HpBar.h
@brief プレイヤーの体力を表示するバー
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"
#include <vector>

namespace basecross {

	class HpBar : public GameObject
	{
		float m_maxHP;

		// HPバーの情報を入れる変数
		shared_ptr<GaugeSizeSettings> m_bar;

	public:
		HpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxHP(0)
		{
		}

		// 初期化 //
		void OnCreate() override;
		// 更新処理 //
		void OnUpdate() override;
		// 描画処理 //
		void OnDraw() override;
	};
}
//end basecross

