/*!
@file Sprites.cpp
@brief �X�v���C�g�̐e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	Sprites::~Sprites() {}

	void Sprites::OnCreate()
	{
	}

	void Sprites::CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey)
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f	 , 0.0f	   , 0.0f), white, Vec2(0.0f, 0.0f)}, // ����
			{Vec3(size.x , 0.0f	   , 0.0f), white, Vec2(1.0f, 0.0f)}, // �E��
			{Vec3(0.0f	 , -size.y , 0.0f), white, Vec2(0.0f, 1.0f)}, // ����
			{Vec3(size.x , -size.y , 0.0f), white, Vec2(1.0f, 1.0f)}, // �E��
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(texKey);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(position);

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::ForeFront);
	}
}