/*!
@file RandomSelectLevelUp.cpp
@brief ランダムにレベルアップできる項目を出すクラスの実装
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	RandomSelectLevelUp::RandomSelectLevelUp(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end コンストラクタ

	RandomSelectLevelUp::~RandomSelectLevelUp()
	{
	} // end デストラクタ

	void RandomSelectLevelUp::OnCreate()
	{

	} // end OnCreate

	void RandomSelectLevelUp::RandomSelect(int selectStatus)
	{
		int i, j; // ループ用変数
		int selectNum = selectStatus;
		int commandNum[m_PickUpStatusCount] = { 0 }; // 乱数格納用配列
		srand((unsigned int)time(NULL));

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do { // 重複を解消
				
				commandNum[i] =	rand() % selectNum;
				for (j = 0; j < i; j++)
				{
					if (commandNum[i] == commandNum[j])
					{
						break;
					}
				}
			} while (i != j);
			m_CommandNums[i] = commandNum[i];
			GetStage()->AddGameObject<LevelUpSprites>(m_CommandNums[i], true, Vec2(516.0f, 128.0f), Vec2(300.0f, 300.0f + -(i * 128.0f) + -(i * 20)), i);
		}
	} // end RandomSelect

	void RandomSelectLevelUp::OnUpdate()
	{
		/* プレイヤーのステータスからexpの取得量を取得
		* 取得したexpが一定数を超えた時にRandomSelectを実行
		*/

		// テスト用 //
		auto& app = App::GetApp();
		// ゲームパッドを使用する
		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			RandomSelect(8);
		}
	}
}
//end basecross
