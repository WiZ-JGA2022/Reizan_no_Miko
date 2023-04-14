/**
@file GameSprite.cpp
@brief �����̕\���̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameSprite::GameSprite(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	GameSprite::~GameSprite() {}

	void GameSprite::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		m_vertices = {
			{Vec3(0.0f		, 0.0f		 , 0.0f), white, Vec2(0.0f, 0.0f)}, // ����
			{Vec3(m_UiSize.x, 0.0f		 , 0.0f), white, Vec2(1.0f, 0.0f)}, // �E��
			{Vec3(0.0f		, -m_UiSize.y, 0.0f), white, Vec2(0.0f, 1.0f)}, // ����
			{Vec3(m_UiSize.x, -m_UiSize.y, 0.0f), white, Vec2(1.0f, 1.0f)}, // �E��
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_position = Vec3(280.0f, app->GetGameHeight() * 0.5f, 0.0f);

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"GAME_SPRITE");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
	}
}