/*!
@file RandomSelectLevelUpButton.cpp
@brief �����_���Ƀ��x���A�b�v�ł��鍀�ڂ��o���N���X�̎���
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	RandomSelectLevelUpButton::RandomSelectLevelUpButton(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	} // end �R���X�g���N�^

	RandomSelectLevelUpButton::~RandomSelectLevelUpButton() {} 
	// end �f�X�g���N�^

	void RandomSelectLevelUpButton::OnCreate()
	{
	} // end OnCreate

	void RandomSelectLevelUpButton::RandomSelect(int selectStatus)
	{
		int i, j; // ���[�v�p�ϐ�
		int spriteNums[m_PickUpStatusCount] = { 0 }; // �����i�[�p�z��
		srand((unsigned int)time(NULL));
		GetStage()->AddGameObject<EventBackGround>();
		for (i = 0; i < m_PickUpStatusCount; i++)
		{
			do { // �d��������
				
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
			GetStage()->AddGameObject<LevelUpSprites>(m_spriteNums[i], true, Vec2(516.0f, 192.0f), Vec2(250.0f, 200.0f + -(i * 192.0f) + -(i * 20)), i);
			GetStage()->AddGameObject<CrossKeySprites>(i, true, Vec2(64.0f, 64.0f), Vec2(40.0f, 200.0f + -(i * 192.0f) + -(i * 20)), i);
		}
	} // end RandomSelect

	void RandomSelectLevelUpButton::LevelUpEvent()
	{
		m_isActiveSprite = true;
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"LEVELUP_SE", 0, 0.1f);
		RandomSelect(6);		
	}
}
//end basecross
