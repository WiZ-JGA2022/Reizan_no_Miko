/* !
@file TrapUI.h
@brief ƒgƒ‰ƒbƒvUI‚ÌÀ‘•
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

	// ‰Šú‰»
	void TutorialUI::OnCreate()
	{
		Sprites::CreateSprite(Vec3(350.0f, 250.0f, 0.0f), Vec2(250.0f, 200.0f), L"TUTORIAL", false, true);
	} // end OnCreate
}
