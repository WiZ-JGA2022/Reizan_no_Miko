/**
@file HpNumber.cpp
@brief ����HP�ƍő�HP�𐔎��ŕ\������UI�̎���
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
		//m_numbers.reserve(m_place);

		//for (int i = 0; i < m_place; i++)
		//{
		//	auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"HP_NUMBER"); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
		//	numberObj->SetPosition(Vec2(App::GetApp()->GetGameWidth() + 400.0f + m_Size.x * i, 0.0f), 0.49f); // ��ʂ̉E�[����A�X�R�A�̂��ׂĂ̌������܂�ʒu�ɒ�������
		//	m_numbers.push_back(numberObj);
		//}

	}

	//void HpNumber::OnUpdate()
	//{
	//	auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
	//	if (levelUpEvent->GetEventActive())
	//	{
	//		return;
	//	}

	//	auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

	//	if (m_maxHp < playerStatus->GetStatusValue(L"HP"))
	//	{
	//		m_maxHp = playerStatus->GetStatusValue(L"HP");
	//	}
	//	UpdateValue(m_maxHp, true);
	//	UpdateValue(playerStatus->GetStatusValue(L"HP"), false);
	//}

	//void HpNumber::OnDraw()
	//{
	//	//for (auto& number : m_numbers)
	//	//{
	//	//	number->OnDraw();
	//	//}
	//}

	//void HpNumber::UpdateValue(float Hp, bool isMax)
	//{
	//	//if (isMax)
	//	//{
	//	//	int place = 10000; 
	//	//	for (auto& numberObj : m_numbers)
	//	//	{
	//	//		int number = (int)Hp / place % 10; // �X�R�A�̒l����w��́u�ʁv�����A���̎���1�̈ʂ�]��Ƃ��Ďc��
	//	//		numberObj->SetNumber(number); // ���݂̌����\�����l�����Ƀi���o�[�I�u�W�F�N�g�̕\�����e��ݒ肷��

	//	//		place *= 10; // �������炷
	//	//	}

	//	//}
	//	//else
	//	//{
	//	//	int place = 1;
	//	//	for (auto& numberObj : m_numbers)
	//	//	{
	//	//		int number = (int)Hp / place % 10; // �X�R�A�̒l����w��́u�ʁv�����A���̎���1�̈ʂ�]��Ƃ��Ďc��
	//	//		numberObj->SetNumber(number); // ���݂̌����\�����l�����Ƀi���o�[�I�u�W�F�N�g�̕\�����e��ݒ肷��

	//	//		place *= 10; // �������炷
	//	//	}
	//	//}
	//}
}