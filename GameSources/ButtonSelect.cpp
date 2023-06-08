/*!
@file ButtonSelect.cpp
@brief ボタンUIを複数実装
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	ButtonSelect::ButtonSelect(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end コンストラクタ

	ButtonSelect::~ButtonSelect() {}
	// end デストラクタ

	//初期化
	void ButtonSelect::OnCreate()
	{

		/*auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"LEVELUP_SE", 0, 0.1f);*/

		for (int i = 0; i < m_PickUpStatusCount; i++)
		{
			GetStage()->AddGameObject<ButtonSprite>(i, true, Vec2(75.0f, 75.0f), Vec2(-500.0f + (i * 250.0f) + (i * 20), -300.0f), i);	//連続で表示する複数の画像の位置座標の設定
		}
	} // end OnCreate



}
