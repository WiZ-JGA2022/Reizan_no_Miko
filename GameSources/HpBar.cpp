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

		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
		m_bar->UpdateGaugeSize(playerStatus->GetStatusValue(L"HP"), playerStatus->GetStatusValue(L"HP"));
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	void HpBar::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		if (m_maxHP < playerStatus->GetStatusValue(L"HP"))
		{
			m_maxHP = playerStatus->GetStatusValue(L"HP");
		}
		m_bar->UpdateGaugeSize(m_maxHP, playerStatus->GetStatusValue(L"HP"));
	}

	void HpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
