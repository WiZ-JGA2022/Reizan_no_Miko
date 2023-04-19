/* !
* 
@file ExpBar.h
@brief 経験値を表示するバー
*
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"

namespace basecross {
	
	class ExpBar : public GameObject
	{
		int m_maxExp; // 最大経験値

		// EXPバーの情報を入れる変数
		shared_ptr<GaugeSizeSettings> m_bar[2];

	public:
		ExpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxExp(0)
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
