/* !
@file TitleSprite.h
@brief �^�C�g���V�[���̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TitleSprite : public Sprites {
		const Vec2 m_DefaultSize;

	public:
		TitleSprite(const shared_ptr<Stage>& stage);
		~TitleSprite();

		void OnCreate() override;
		void OnUpdate() override;

	};
}