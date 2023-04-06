/*!
@file RandomSelectLevelUpButton.cpp
@brief ランダムにレベルアップできる項目を出すクラスの実装
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	RandomSelectLevelUpButton::RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end コンストラクタ

	RandomSelectLevelUpButton::~RandomSelectLevelUpButton()
	{
	} // end デストラクタ

	void RandomSelectLevelUpButton::OnCreate()
	{
	} // end OnCreate

	void RandomSelectLevelUpButton::RandomSelect(int selectStatus)
	{
		int i, j; // ループ用変数
		int spriteNums[m_PickUpStatusCount] = { 0 }; // 乱数格納用配列
		srand((unsigned int)time(NULL));

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do { // 重複を解消
				
				spriteNums[i] =	rand() % selectStatus;
				for (j = 0; j < i; j++)
				{
					if (spriteNums[i] == spriteNums[j])
					{
						break;
					}
				}
			} while (i != j);
			m_spriteNums[i] = spriteNums[i];
			GetStage()->AddGameObject<LevelUpSprites>(m_spriteNums[i], true, Vec2(516.0f, 192.0f), Vec2(250.0f, 300.0f + -(i * 192.0f) + -(i * 20)), i);
			GetStage()->AddGameObject<CrossKeySprites>(i, true, Vec2(64.0f, 64.0f), Vec2(40.0f, 300.0f + -(i * 192.0f) + -(i * 20)), i);
		}
	} // end RandomSelect

	void RandomSelectLevelUpButton::LevelUpEvent()
	{
		auto& app = App::GetApp();
		// ゲームパッドを使用する
		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			m_isActiveSprite = true;
			RandomSelect(6);
		}
		// 十字キーの上、右、下で選ぶ
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus")->StatusLevelUpdate(m_spriteNums[0]);
			m_isActiveSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus")->StatusLevelUpdate(m_spriteNums[1]);
			m_isActiveSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus")->StatusLevelUpdate(m_spriteNums[2]);
			m_isActiveSprite = false;
		}

	}
}
//end basecross
