/**
@file TimeChara.h
@brief �����̕\���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	TimeChara::TimeChara(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(128.0f, 25.6f))
	{
	}
	// �f�X�g���N�^
	TimeChara::~TimeChara() {}

	// ������
	void TimeChara::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-64.0f, App::GetApp()->GetGameHeight() * 0.5f, 0.0f), m_DefaultSize, L"TIME_CHARA");
	}

	// �X�V����
	void TimeChara::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}