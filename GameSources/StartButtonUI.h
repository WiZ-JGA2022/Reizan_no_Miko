/* !
@file StartButtonUI.h
@brief タイトルシーンのスタートボタン
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StartSprite : public Sprites {
		const Vec2 m_DefaultSize;//初期サイズ

		bool m_changeSpeed; //ボタンが押されたら点滅速度変更フラグ

	public:
		//コンストラクタ
		StartSprite(const shared_ptr<Stage>& stage);
		//デストラクタ
		~StartSprite();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

	};
}
