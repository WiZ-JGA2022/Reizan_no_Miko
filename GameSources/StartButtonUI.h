/* !
@file StartButtonUI.h
@brief タイトルシーンのスタートボタン
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StartSprite : public Sprites {
		const Vec2 m_DefaultSize;

		bool m_changeSpeed;

	public:
		StartSprite(const shared_ptr<Stage>& stage);
		~StartSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}
