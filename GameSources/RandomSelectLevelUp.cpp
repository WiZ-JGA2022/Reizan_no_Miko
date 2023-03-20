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
	}

	int RandomSelectLevelUp::CommandNum()
	{
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
		int commandnum = sixteen * two;
		return commandnum;
	}
	//コマンドの表示
	void RandomSelectLevelUp::CommandCount(int maxC)
	{
		for (int i = 0; i < maxC + 1; i++)
		{
			//今のコマンドの回数でボタンの判断
			m_CommandNums.emplace_back(CommandNum());

			GetStage()->AddGameObject<LevelUpSprites>(m_CommandNums[i], true, Vec2(516.0f, 128.0f), Vec2(300.0f, 300.0f + -(i * 128.0f) + -(i * 20)), i);
		}
	}

}
//end basecross
