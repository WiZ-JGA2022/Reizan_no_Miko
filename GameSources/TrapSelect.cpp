/*!
@file RandomSelectLevelUpButton.cpp
@brief ランダムにレベルアップできる項目を出すクラスの実装
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	TrapSelect::TrapSelect(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end コンストラクタ

	TrapSelect::~TrapSelect() {}
	// end デストラクタ

	void TrapSelect::OnCreate()
	{
		for (int i = 0; i < m_PickUpStatusCount; i++)
		{
			GetStage()->AddGameObject<TrapSprite>(i, true, Vec2(75.0f, 75.0f), Vec2(-400.0f + (i * 250.0f) + (i * 20), -300.0f), i);
		}
	} // end OnCreate



}
