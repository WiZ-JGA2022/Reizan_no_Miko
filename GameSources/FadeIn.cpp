/* !
@file FadeIn.cpp
@brief �t�F�[�h�C���̎���
@prod �F�� �S�I
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^�ƃf�X�g���N�^
	FadeIn::FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight())),
		m_texKey(texKey)
	{
	}
	FadeIn::~FadeIn() {}
	// �����܂�

	void FadeIn::OnCreate()
	{
		// �����l�̐ݒ�(�c�A�����A��)
		Sprites::CreateFadeSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, m_texKey, FadeType::FadeIn);
	}
	
	void FadeIn::OnUpdate()
	{
		Sprites::UpdateFadeSprite(1.0f);
	}
}