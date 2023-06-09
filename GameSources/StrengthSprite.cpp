/* !
@file StrengthSprite.cpp
@brief 耐久値スプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	StrengthSprite::StrengthSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(64.0f, 24.0f))
	{
	}
	// デストラクタ
	StrengthSprite::~StrengthSprite() {}

	// 初期化
	void StrengthSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-240.0f, 392.0f, 0.0f), m_DefaultSize, L"STRENGTH");
	}
}