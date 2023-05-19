/* !
@file TutorialUI.h
@brief �`���[�g���A��UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TutorialUI::TutorialUI(const shared_ptr<Stage>& stage
	) :
		Sprites(stage),
		m_DefaultSize(Vec2(250.0f, 200.0f)),
		m_AfterSize(Vec2(0.0f, 0.0f))
	{
	}

	// ������
	void TutorialUI::OnCreate()
	{
		Sprites::CreateSeekSizeSprite(Vec3(350.0f, 0.0f, 0.0f), m_DefaultSize, m_AfterSize, L"TUTORIAL", SeekType::BottomRight, 5.0f);
	}

	void TutorialUI::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}
