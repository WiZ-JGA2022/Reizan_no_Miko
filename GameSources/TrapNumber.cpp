/**
@file TrapNumber.cpp
@brief 㩂�u���鐔�𐔎��ŕ\������UI
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�R���X�g���N�^�ƃf�X�g���N�^
	TrapNumber::TrapNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(5)
	{
	}
	TrapNumber::~TrapNumber() {}
	//�I��

	//������
	void TrapNumber::OnCreate()
	{
		for (int i = 0; i < 4; i++)
		{
			m_numbers[i].reserve(m_place);

			for (int j = 0; j < m_place; j++)
			{
				auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"TRAP_NUMBER"); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
				numberObj->SetPosition(Vec2((220.0f + (270.0f * i)) - m_Size.x * j, 0.0f), -0.42f); // ��ʂ̉E�[����A�X�R�A�̂��ׂĂ̌������܂�ʒu�ɒ�������
				m_numbers[i].push_back(numberObj);
			}
		}
	}

	//�X�V����
	void TrapNumber::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		for (int i = 0; i < 2; i++)
		{
			UpdateValue(player->GetTrapLimit(i), player->GetTrapLimit(i) - player->GetTrapCount(i), i);
		}

		if (player->GetCondition() == 1) {
			// �����I����ɕ\�������摜����������

			GetStage()->RemoveGameObject<TrapNumber>(GetThis<TrapNumber>());

		}
	}

	//�`�揈��
	void TrapNumber::OnDraw()
	{
		for (int i = 0; i < 2; i++) // 2�͏����I��4�ɂ���
		{
			for (auto& number : m_numbers[i])
			{
				number->OnDraw();
			}
		}
	}

	void TrapNumber::UpdateValue(int trapLimit, int currentTrapCount, int index)
	{
		int place = 1;
		for (auto& numberObj : m_numbers[index])
		{
			int maxNumber = trapLimit / place % 10; // 1���ڂ���\��
			int currentNumber = currentTrapCount * 1000 / place % 10; // 4���ڈȍ~�ɕ\��
			int srash = 10;
			if (place == 100)
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