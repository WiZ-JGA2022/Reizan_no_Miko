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
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		m_bar[0] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBAR");		//�ʒu���W�A�\�[�X�摜
		m_bar[1] = ObjectFactory::Create<GaugeSizeSettings>(GetStage(), 200.0f, L"HOLDBARFRAME");	//�ʒu���W�A�\�[�X�摜
		m_bar[0]->UpdateGaugeSize(m_maxTime,(float)time->GetSkipTime());
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);
		m_bar[0]->SetPosition(275.0f, -330.0f, 0.0f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
		m_bar[1]->SetPosition(275.0f, -330.0f, 0.0f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
	}

	//�X�V����
	void HoldBar::OnUpdate()
	{
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");	//TimeNumber�̎擾
		m_bar[0]->UpdateGaugeSize(m_maxTime, (float)time->GetSkipTime());	//�Q�[�W�̏��
		m_bar[1]->UpdateGaugeSize(m_maxTime, (float)m_maxTime);				//�Q�[�W�̏��
	}

	//�`�揈��
	void HoldBar::OnDraw()
	{
		m_bar[0]->GameObject::OnDraw();
		m_bar[1]->GameObject::OnDraw();

	}
}
//end basecross
