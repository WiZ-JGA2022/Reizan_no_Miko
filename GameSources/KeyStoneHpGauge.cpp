/*!
@file KeyStoneHpGauge.cpp
@brief �v�΂̗̑͂�\������o�[�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		// KeyStone�I�u�W�F�N�g�̎擾
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");

		// �Q�[�W�̐���
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_GREEN");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, L"HPBAR_RED");

		// �Q�[�W�T�C�Y�̐ݒ�
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());

		// ��ʂ̍���ɕ\��
		m_bar[0]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); 
		m_bar[1]->SetPosition((float)App::GetApp()->GetGameWidth(), 0.0f, 0.49f); 
	}

	void HpBar::OnUpdate()
	{
		// �Q�[�W�T�C�Y�̍X�V
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
		m_bar[0]->UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
		m_bar[1]->UpdateGaugeSize(stone->GetMaxHp(), (float)stone->GetMaxHp());
	}

	void HpBar::OnDraw()
	{
		// �Q�[�W�̕`��
		m_bar[1]->GameObject::OnDraw();
		m_bar[0]->GameObject::OnDraw();
	}
}
//end basecross
