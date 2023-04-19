/*!
@file HpBar.cpp
@brief �v���C���[�̗̑͂�\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true, true);
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true, false);
		m_bar[0]->UpdateGaugeSize(playerStatus->GetMaxHp(), playerStatus->GetStatusValue(L"HP"));
		m_bar[1]->UpdateGaugeSize(playerStatus->GetMaxHp(), (float)playerStatus->GetMaxHp());
		m_bar[0]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
		m_bar[1]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	void HpBar::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		m_bar[0]->UpdateGaugeSize(playerStatus->GetMaxHp(), playerStatus->GetStatusValue(L"HP"));
		m_bar[1]->UpdateGaugeSize(playerStatus->GetMaxHp(), (float)playerStatus->GetMaxHp());
	}

	void HpBar::OnDraw()
	{
		m_bar[1]->GameObject::OnDraw();
		m_bar[0]->GameObject::OnDraw();
	}
}
//end basecross
