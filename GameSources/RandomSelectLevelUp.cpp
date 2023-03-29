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
		int commandNum[m_PickUpStatusCount] = { 0 }; // 乱数格納用配列
		srand((unsigned int)time(NULL));

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do { // 重複を解消
				
				commandNum[i] =	rand() % selectStatus;
				for (j = 0; j < i; j++)
				{
					if (commandNum[i] == commandNum[j])
					{
						break;
					}
				}
			} while (i != j);
			m_CommandNums[i] = commandNum[i];
			GetStage()->AddGameObject<LevelUpSprites>(m_CommandNums[i], true, Vec2(516.0f, 192.0f), Vec2(250.0f, 300.0f + -(i * 192.0f) + -(i * 20)), i);
		}
	} // end RandomSelect

	void RandomSelectLevelUpButton::OnUpdate()
	{
		/* プレイヤーのステータスからexpの取得量を取得
		* 取得したexpが一定数を超えた時にRandomSelectを実行
		*/

		// テスト用 //
		auto& app = App::GetApp();
		// ゲームパッドを使用する
		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		// テスト用にBボタンでレベルアップイベントを実行
		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			ControllerSprite = true;

			RandomSelect(8);
		}

		// 十字キーの上、右、下で選ぶ
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			ControllerSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			ControllerSprite = false;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			ControllerSprite = false;
		}
	}
}
//end basecross
