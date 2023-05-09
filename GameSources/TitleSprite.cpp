/* !
@file TitleSprite.h
@brief �^�C�g���V�[���̔w�i�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TitleSprite::TitleSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	TitleSprite::~TitleSprite() {}

	void TitleSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"TITLE",false);

	}
}