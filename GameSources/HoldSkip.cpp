/* !
@file HoldSkip.cpp
@brief HoldSkip�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	HoldSkipSprite::HoldSkipSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f))	//�T�C�Y�̏����ݒ�
	{
	}
	HoldSkipSprite::~HoldSkipSprite() {}

	void HoldSkipSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 300.0f, 0.0f), m_DefaultSize, L"HOLDDOWN_SKIP");
	}

	void HoldSkipSprite::OnUpdate()
	{
	}
}
