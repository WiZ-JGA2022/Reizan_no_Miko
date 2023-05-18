/*!
@file ExpBar.cpp
@brief �o���l��\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HoldBar::OnCreate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");
		//m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"EXPBAR_BLACK");
		m_bar[0]->UpdateGaugeSize(m_maxExp, 15);
		//m_bar[1]->UpdateGaugeSize(m_maxExp, 3);
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
		//m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	void HoldBar::OnUpdate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

		if (m_maxExp < playerStatus->GetMaxExp())
		{
			m_maxExp = playerStatus->GetMaxExp();
		}
		m_bar[0]->UpdateGaugeSize(m_maxExp, 15);
		//m_bar[1]->UpdateGaugeSize(m_maxExp, (float)3);
	}

	void HoldBar::OnDraw()
	{
		m_bar[0]->GameObject::OnDraw();
		//m_bar[1]->GameObject::OnDraw();
	}
}
//end basecross
