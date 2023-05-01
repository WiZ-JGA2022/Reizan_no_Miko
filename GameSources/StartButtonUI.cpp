/* !
@file StartbuttonUI.h
@brief �^�C�g���V�[���̃{�^���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float m_startScaleZ = 1.0f;// �傫��
	constexpr float m_startPosZ = 1.0f;	 // ���s��
	constexpr float m_helfSize = 0.5f;	 // �����̑傫��


	StartSprite::StartSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage)
	{
	}
	StartSprite::~StartSprite() {}

	void StartSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(50,-100, 0.0f), m_DefaultSize, L"START_UI",true,false);
	}
}