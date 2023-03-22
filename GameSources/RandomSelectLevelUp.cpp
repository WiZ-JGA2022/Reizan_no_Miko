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
	} // end �R���X�g���N�^

	RandomSelectLevelUp::~RandomSelectLevelUp()
	{
	} // end �f�X�g���N�^

	void RandomSelectLevelUp::OnCreate()
	{

	} // end OnCreate

	void RandomSelectLevelUp::RandomSelect()
	{
		int i, j; // ���[�v�p�ϐ�
		int commandNum[m_PickUpStatusCount] = { 0 }; // �����i�[�p�z��

		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do {
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
		/* �v���C���[�̃X�e�[�^�X����exp�̎擾�ʂ��擾
		* �擾����exp����萔�𒴂�������PickUpBotton�����s
		* 
		*/
	}
}
//end basecross
