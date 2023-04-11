/**
@file ExpNumber.cpp
@brief ����EXP�ƍő�EXP�𐔎��ŕ\������UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ExpNumber::ExpNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(7),
		m_maxExp(0)
	{
	}
	ExpNumber::~ExpNumber() {}

	void ExpNumber::OnCreate()
	{
		m_numbers.reserve(m_place);

		for (int i = 0; i < m_place; i++)
		{
			auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"EXP_NUMBER"); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
			numberObj->SetPosition(Vec2(480.0f - m_Size.x * i, 0.0f), 0.46f); // ��ʂ̉E�[����A�X�R�A�̂��ׂĂ̌������܂�ʒu�ɒ�������
			m_numbers.push_back(numberObj);
		}
	}

	void ExpNumber::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		UpdateValue(playerStatus->GetMaxExp(), playerStatus->GetStatusValue(L"EXP"));
	}

	void ExpNumber::OnDraw()
	{
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}

	void ExpNumber::UpdateValue(int maxExp, float currentExp)
	{
		int place = 1;
		for (auto& numberObj : m_numbers)
		{
			int currentNumber = (int)currentExp * 10000 / place % 10; // 4���ڈȍ~�ɕ\��
			int maxNumber = maxExp / place % 10; // 1���ڂ���\��
			int srash = 10;
			if (place == 1000)
			{
				numberObj->SetNumber(srash); // 3���ڂɃX���b�V����\��
			}
			else
			{
				numberObj->SetNumber(currentNumber + maxNumber); // ���݂̌����\�����l�����Ƀi���o�[�I�u�W�F�N�g�̕\�����e��ݒ肷��
			}

			place *= 10; // �������炷
		}
	}
}
