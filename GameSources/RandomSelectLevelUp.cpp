/*!
@file RandomSelectLevelUp.cpp
@brief ランダムにレベルアップできる項目を出すクラスの実装
*/

#include "stdafx.h"
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

	void RandomSelectLevelUp::RandomSelect()
	{
		int i, j; // ループ用変数
		int commandNum[m_PickUpStatusCount] = { 0 }; // 乱数格納用配列

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do {
				int a = rand() % 4;
				//0x0000の一桁目か四桁目を指定する
				if (a <= 1)
				{
					a = 0;
				}
				else
				{
					a = 3;
				}
				//A～Ⅹボタン、上下左右ボタンに割り当てられている数字をランダムに設定
				int sixteen = (int)std::pow(16, a);
				int b = rand() % 4;
				int two = (int)std::pow(2, b);
				commandNum[i] = sixteen * two;
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
		* 取得したexpが一定数を超えた時にPickUpBottonを実行
		* 
		*/
	}
}
//end basecross
