/* !
@file TrapUI.h
@brief トラップUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {

	class TutorialUI : public Sprites {
		const Vec2 m_DefaultSize; //初期サイズ
		const Vec2 m_AfterSize; // 変更後のサイズ
	public:
		//コンストラクタ
		TutorialUI(const shared_ptr<Stage>& stagePtr);
		//デストラクタ
		virtual ~TutorialUI() {}

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;
	};
}
//end basecross
