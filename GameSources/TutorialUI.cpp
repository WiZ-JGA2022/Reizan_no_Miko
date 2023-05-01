/* !
@file TrapUI.h
@brief トラップUIの実装
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {
	TutorialUI::TutorialUI(const shared_ptr<Stage>& stage
	) :
		Sprites(stage)
	{
	}

	// 初期化
	void TutorialUI::OnCreate()
	{
		Sprites::CreateSprite(Vec3(300.0f, 250.0f, 0.0f), Vec2(200.0f, 200.0f), L"TUTORIAL", false, true);
	} // end OnCreate
}
