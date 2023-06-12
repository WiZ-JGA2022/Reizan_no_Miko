/**
@file HpNumber.cpp
@brief ����HP�ƍő�HP�𐔎��ŕ\������UI�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	HpNumber::HpNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(7),
		m_maxHp(0)
	{
	}
	HpNumber::~HpNumber() {}

	void HpNumber::OnCreate()
	{
		m_numbers.reserve(m_place);

		for (int i = 0; i < m_place; i++)
		{
			auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"HP_NUMBER"); 
			numberObj->SetPosition(Vec2(535.0f - m_Size.x * i, 0.0f), 0.49f); 
			m_numbers.push_back(numberObj);
		}
	}

	void HpNumber::OnUpdate()
	{
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
		if (!(stone->GetCurrentHp() < 0.0f))
		{
			// �l�̍X�V
			UpdateValue(stone->GetMaxHp(), stone->GetCurrentHp());
		}
	}

	void HpNumber::OnDraw()
	{
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}

	void HpNumber::UpdateValue(int maxHp, float currentHp)
	{
		int place = 1; // ���̏����ʒu��ݒ�
		for (auto& numberObj : m_numbers)
		{
			int maxNumber = maxHp / place % 10; // 1���ڂ���\��
			int currentNumber = (int)currentHp * 10000 / place % 10; // 5���ڈȍ~�ɕ\��
			int srash = 10;
			if (place == 1000)
			{
				numberObj->SetNumber(srash); // 4���ڂɃX���b�V����\��
			}
			else
			{
				numberObj->SetNumber(currentNumber + maxNumber); // ���݂̌����\�����l�����Ƀi���o�[�I�u�W�F�N�g�̕\�����e��ݒ肷��
			}

			place *= 10; // �������炷
		}
	}
}