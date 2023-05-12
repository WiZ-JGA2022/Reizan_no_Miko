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
		m_selected(false),
		m_changeSize(false),
		m_fadeCount(0.0f)
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
			m_TotalTime += 0.75f;
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

		if (m_changeSize)
		{
			// 時間の更新
			auto& app = App::GetApp();
			auto delta = app->GetElapsedTime();

			m_TotalTime += delta;

			if (m_TotalTime > 5.0f && m_isState != TutorialState::Stop)
			{
				m_isState = TutorialState::SizeChange;
			}
			if (m_isState == TutorialState::SizeChange)
			{
				m_tutorialUiSize += 0.05f;
				m_vertices[0].position.x = m_spriteSize.x * m_tutorialUiSize;
				m_vertices[0].position.y = -m_spriteSize.y * m_tutorialUiSize;
				m_vertices[1].position.y = -m_spriteSize.y * m_tutorialUiSize;
				m_vertices[2].position.x = m_spriteSize.x * m_tutorialUiSize;

				auto drawComp = GetComponent<PCTSpriteDraw>();
				drawComp->UpdateVertices(m_vertices);

				if (m_tutorialUiSize > 1.0f)
				{
					m_isState = TutorialState::Stop;
				}
			}

		}

		if (m_fade)
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto& pad = device.GetControlerVec()[0];

			if (m_fadeType == FadeType::FadeIn)
			{
				m_fadeCount -= 0.01;

				auto drawComp = GetComponent<PCTSpriteDraw>();
				m_vertices[0].color = Col4(0.0f, 0.0f, 0.0f, m_fadeCount);
				m_vertices[1].color = Col4(0.0f, 0.0f, 0.0f, m_fadeCount);
				m_vertices[2].color = Col4(0.0f, 0.0f, 0.0f, m_fadeCount);
				m_vertices[3].color = Col4(0.0f, 0.0f, 0.0f, m_fadeCount);
				drawComp->SetDiffuse(m_vertices[0].color);
				drawComp->UpdateVertices(m_vertices);
			}
			if (m_fadeType == FadeType::FadeOut)
			{
				m_fadeCount += 0.01;

				auto drawComp = GetComponent<PCTSpriteDraw>();
				m_vertices[0].color = Col4(1.0f, 1.0f, 1.0f, m_fadeCount);
				m_vertices[1].color = Col4(1.0f, 1.0f, 1.0f, m_fadeCount);
				m_vertices[2].color = Col4(1.0f, 1.0f, 1.0f, m_fadeCount);
				m_vertices[3].color = Col4(1.0f, 1.0f, 1.0f, m_fadeCount);
				drawComp->SetDiffuse(m_vertices[0].color);
				drawComp->UpdateVertices(m_vertices);
			}

		}

	}

	void Sprites::CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey, bool Trace, bool changeSize)
	{
		m_Trace = Trace;
		m_changeSize = changeSize;
		m_spriteSize = size;
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
		m_draw->SetDiffuse(white);
		m_draw->SetTextureResource(texKey);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(position);

		// 透過処理を有効にする
		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::ForeFront);
	}
	void Sprites::CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey, bool Trace, bool fade, int fadeType){
		m_fade = fade;
		if (m_fade) {
			m_fadeType = (FadeType)fadeType;
			if (m_fadeType == FadeType::FadeOut) {
				m_fadeCount = 0.0f;
			}
			else if(m_fadeType == FadeType::FadeIn)
			{
				m_fadeCount = 1.0f;
			}
		}
		CreateSprite(position, size, texKey, Trace,fade);
	}
	
}