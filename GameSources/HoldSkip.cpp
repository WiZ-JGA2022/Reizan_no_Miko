/* !
@file HoldSkip.cpp
@brief �������ŃX�L�b�v�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	HoldSkipSprite::HoldSkipSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(150.0f, 150.0f))	//�T�C�Y�̏����ݒ�
	{
	}
	//�f�X�g���N�^
	HoldSkipSprite::~HoldSkipSprite() {}

	//������
	void HoldSkipSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(400.0f, 300.0f, 0.0f), m_DefaultSize, L"HOLDDOWN_SKIP");	//�ʒu���W,�T�C�Y,�\�[�X�摜
	}

	//�X�V����
	void HoldSkipSprite::OnUpdate()
	{
	}
}
