/*!
@file ExpBar.cpp
@brief �o���l��\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	// �e�X�g�p
	int currentExp = 0;
	int delay = 120;
	// �����܂�

	void ExpBar::OnCreate()
	{
		m_bar = ObjectFactory::Create<GaugeSizeSettings>(GetStage(),200.0f, false); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
		m_bar->UpdateGaugeSize(10.0f, currentExp);
		m_bar->SetPosition(App::GetApp()->GetGameWidth(), 0.0f, 0.46f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	// �X�V���� //
	void ExpBar::OnUpdate()
	{
		// �e�X�g�p //
		delay--;
		if (delay < 0)
		{
			currentExp += 1;
			delay = 120;
		}
		// �����܂� //

		m_bar->UpdateGaugeSize(10.0f, currentExp);
	}

	// �`�揈�� //
	void ExpBar::OnDraw()
	{
		m_bar->GameObject::OnDraw();
	}
}
//end basecross
