/*!
@file Sprites.cpp
@brief スプライトの親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_TotalTime(0.0f),
		m_selected(false)
	{
	}
	Sprites::~Sprites() {}

	void Sprites::OnCreate()
	{
	}

	void Sprites::OnUpdate()
	{
		if (m_Trace)
		{
			m_TotalTime += 0.75;
			float a = sinf(m_TotalTime);
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto& pad = device.GetControlerVec()[0];

			if (pad.wPressedButtons & XINPUT_GAMEPAD_B)
			{
				m_selected = true;

			}

			if (m_selected)
			{
				auto drawComp = GetComponent<PCTSpriteDraw>();
				m_vertices[0].color = Col4(a, a, a, 1.0f);
				m_vertices[1].color = Col4(a, a, a, 1.0f);
				m_vertices[2].color = Col4(a, a, a, 1.0f);
				m_vertices[3].color = Col4(a, a, a, 1.0f);
				drawComp->UpdateVertices(m_vertices);
			}
		}
		
	}

	void Sprites::CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey,bool Trace)
	{
		m_Trace = Trace;
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f	 , 0.0f	   , 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(size.x , 0.0f	   , 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(0.0f	 , -size.y , 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(size.x , -size.y , 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(texKey);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(position);

		// 透過処理を有効にする
		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::ForeFront);
	}
}