/* !
@file TrapUI.h
@brief �g���b�vUI�̎���
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TrapSprite::TrapSprite(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	TrapSprite::~TrapSprite() {}

	void TrapSprite::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		m_vertices = {
			{Vec3(0.0f				, 0.0f				, 0.0f), white, Vec2(0.0f, 0.0f)}, // ����
			{Vec3(m_DefaultSize.x	, 0.0f				, 0.0f), white, Vec2(1.0f, 0.0f)}, // �E��
			{Vec3(0.0f				, -m_DefaultSize.y	, 0.0f), white, Vec2(0.0f, 1.0f)}, // ����
			{Vec3(m_DefaultSize.x	, -m_DefaultSize.y	, 0.0f), white, Vec2(1.0f, 1.0f)}, // �E��
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};



		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"TRAP_1");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_DefaultSize.x * 3.0f, -m_DefaultSize.y * 1.5f, 0.0f);

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
	}
}