/* !
@file TrapUI.h
@brief ƒgƒ‰ƒbƒvUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {

	class TutorialUI : public Sprites {
		const Vec2 m_DefaultSize;
		const Vec2 m_AfterSize;
	public:
		TutorialUI(const shared_ptr<Stage>& stagePtr);
		virtual ~TutorialUI() {}

		void OnCreate() override;
		void OnUpdate() override;
	};
}
//end basecross
