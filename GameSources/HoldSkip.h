/* !
@file HoldSkip.h
@brief HoldSkip
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class HoldSkipSprite : public Sprites {
		const Vec2 m_DefaultSize;	//初期サイズ

	public:
		//コンストラクタ
		HoldSkipSprite(const shared_ptr<Stage>& stage);
		//デストラクタ
		~HoldSkipSprite();

		//初期化
		void OnCreate() override;

	};
}
