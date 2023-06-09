/* !
@file RBButtonUI.cpp
@brief RBButtonUI�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	RBButtonSprite::RBButtonSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f)),
		m_AfterSize(Vec2(170.0f, 170.0f)),
		m_startSe(false)
	{
	}
	// �f�X�g���N�^
	RBButtonSprite::~RBButtonSprite() {}
	//�I��

	// ������
	void RBButtonSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 350.0f, 0.0f), m_DefaultSize, L"RB_BUTTON");	//�ʒu���W�A�����T�C�Y�A�\�[�X�摜
	}

	// �X�V����
	void RBButtonSprite::OnUpdate()
	{

		// �Q�[���p�b�h�̎擾
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];


		if (pad.wButtons & RB_BUTTON)	// ����RB�{�^�������������ꂽ��
		{
			if (!m_startSe)	
			{
				// �t���O��true�ɂ���SE�𗬂�
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Start(L"SKIP_SE", 0, 0.3f);
				m_startSe = true;
			}
			SetSeekSizeState(0);

			Sprites::UpdateSeekSizeSprite(m_AfterSize,10.0f, SeekType::UpperRight);		// �f�t�H���g�T�C�Y�A�ύX���ԁA�V�[�N�^�C�v
			return;
		}
		else
		{
			// �t���O��false�̎�
			m_startSe = false;
			SetSeekSizeState(0);
			Sprites::UpdateSeekSizeSprite(m_DefaultSize, 0.1f, SeekType::UpperRight);	//�f�t�H���g�T�C�Y�A�ύX���ԁA�V�[�N�^�C�v
		}
	}
}
