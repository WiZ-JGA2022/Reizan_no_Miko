/*!
@file RandomSelectLevelUp.cpp
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X�̎���
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
		//0x0000�̈ꌅ�ڂ��l���ڂ��w�肷��
		if (a <= 1)
		{
			a = 0;
		}
		else
		{
			a = 3;
		}
		//A�`�]�{�^���A�㉺���E�{�^���Ɋ��蓖�Ă��Ă��鐔���������_���ɐݒ�
		int sixteen = (int)std::pow(16, a);
		int b = rand() % 4;
		int two = (int)std::pow(2, b);
		int commandnum = sixteen * two;
		return commandnum;
	}
	//�R�}���h�̕\��
	void RandomSelectLevelUp::CommandCount(int maxC)
	{
		for (int i = 0; i < maxC + 1; i++)
		{
			//���̃R�}���h�̉񐔂Ń{�^���̔��f
			m_CommandNums.emplace_back(CommandNum());

			GetStage()->AddGameObject<LevelUpSprites>(m_CommandNums[i], true, Vec2(516.0f, 128.0f), Vec2(300.0f, 300.0f + -(i * 128.0f) + -(i * 20)), i);
		}
	}

}
//end basecross
