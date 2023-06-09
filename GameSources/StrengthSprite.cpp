/* !
@file StrengthSprite.cpp
@brief �ϋv�l�X�v���C�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	StrengthSprite::StrengthSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(64.0f, 24.0f))
	{
	}
	// �f�X�g���N�^
	StrengthSprite::~StrengthSprite() {}

	// ������
	void StrengthSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-240.0f, 392.0f, 0.0f), m_DefaultSize, L"STRENGTH");
	}
}