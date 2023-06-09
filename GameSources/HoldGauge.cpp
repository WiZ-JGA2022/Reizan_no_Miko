/*!
@file HoldGauge.cpp
@brief �������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void HoldBar::OnCreate()
	{
		// timeNumber�I�u�W�F�N�g���擾
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		// �Q�[�W�𐶐�
		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBARFRAME");
		// �Q�[�W�̑傫����ݒ�
		m_bar[0]->UpdateGaugeSize(m_maxTime,(float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
		// ��ʂ̉E��ɕ\��
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); 
		m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f);
	}

	//�X�V����
	void HoldBar::OnUpdate()
	{
		// �Q�[�W�T�C�Y�̍X�V
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");
		m_bar[0]->UpdateGaugeSize(m_maxTime, (float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
	}

	//�`�揈��
	void HoldBar::OnDraw()
	{
		// �Q�[�W�̕`��
		m_bar[0]->GameObject::OnDraw();
		m_bar[1]->GameObject::OnDraw();
	}
}
//end basecross
