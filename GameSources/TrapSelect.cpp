/*!
@file TrapSelect.cpp
@brief トラップを連続で表示させるクラスの実装
@prod 矢吹悠葉
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
		for (int i = 0; i < m_PickUpStatusCount; i++) //for文で連続で表示させる画像の位置座標の処理
		{
			GetStage()->AddGameObject<TrapSprite>(i, true, Vec2(75.0f, 75.0f), Vec2(-400.0f + (i * 250.0f) + (i * 20), -300.0f), i);
		}
	} // end OnCreate



}
