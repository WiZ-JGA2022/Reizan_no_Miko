/*!
@file ExpBar.cpp
@brief �o���l��\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, false); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
		m_bar->UpdateGaugeSize(10.0f, 0.0f);
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	// �X�V���� //
	void ExpBar::OnUpdate()
	{
		m_bar->UpdateGaugeSize(10.0f, 0.0f);
	}

	// �`�揈�� //
	void ExpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
