/* !
@file TutorialUI.h
@brief チュートリアルUIの実装
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

	// 初期化
	void TutorialUI::OnCreate()
	{
		Sprites::CreateSprite(Vec3(350.0f, 0.0f, 0.0f), m_DefaultSize, L"TUTORIAL");
	}

	void TutorialUI::OnUpdate()
	{
		Sprites::UpdateSeekSizeSprite(m_AfterSize, 0.5f, SeekType::BottomRight, 5.0f);
	}
}
