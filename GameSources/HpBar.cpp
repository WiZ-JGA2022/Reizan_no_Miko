/*!
@file HpBar.cpp
@brief �v���C���[�̗̑͂�\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void HpBar::OnCreate()
	{
		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 400.0f, true); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
		m_bar->UpdateGaugeSize(30.0f, 30.0f);
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.49f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	void HpBar::OnUpdate()
	{
		m_bar->UpdateGaugeSize(30.0f, 30.0f);
	}

	void HpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
