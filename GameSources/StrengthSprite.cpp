/* !
@file StrengthSprite.cpp
@brief 耐久値スプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StrengthSprite::StrengthSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(64.0f, 24.0f))
	{
	}
	StrengthSprite::~StrengthSprite() {}

	void StrengthSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-240.0f, 392.0f, 0.0f), m_DefaultSize, L"STRENGTH");
	}

	void StrengthSprite::OnUpdate()
	{
	}
}