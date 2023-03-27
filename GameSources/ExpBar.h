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
		// EXPバーの情報を入れる変数
		shared_ptr<GaugeSizeSettings> m_bar;

	public:
		ExpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
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
