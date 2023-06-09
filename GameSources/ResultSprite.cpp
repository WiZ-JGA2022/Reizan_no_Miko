/* !
@file ResultSprite.cpp
@brief ���U���g�V�[���̔w�i�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �R���X�g���N�^
	ResultSprite::ResultSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// �f�X�g���N�^
	ResultSprite::~ResultSprite() {}

	// ������
	void ResultSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"GAMEOVER");
	}

	// �X�V����
	void ResultSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}

	// �R���X�g���N�^
	ClearSprite::ClearSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// �f�X�g���N�^
	ClearSprite::~ClearSprite() {}

	// ������
	void ClearSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"CLEAR_SPRITE");
	}

	// �X�V����
	void ClearSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}