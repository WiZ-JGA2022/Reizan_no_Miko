/* !
@file RightStick.cpp
@brief �ϋv�l�X�v���C�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	RightStick::RightStick(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(200.0f, 200.0f))
	{
	}
	// �f�X�g���N�^
	RightStick::~RightStick() {}

	// ������
	void RightStick::OnCreate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetBeforePlacedTrap(1) > 0)
		{
			Sprites::CreateSprite(Vec3(-600.0f, -200.0f, 0.0f), m_DefaultSize, L"RIGHT_STICK");
		}
	}
}