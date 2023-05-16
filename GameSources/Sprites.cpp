/*!
@file Sprites.cpp
@brief スプライトの親クラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_spriteSize(Vec2(0.0f)),
		m_afterSize(Vec2(0.0f)),
		m_uiSizeCoefficient(0.0f),
		m_totalTime(0.0f),
		m_alphaNum(0.0f),
		m_fadeSpeed(0.01f)
	{
	}
	Sprites::~Sprites() {}

	void Sprites::OnCreate()
	{
	}

	void Sprites::OnUpdate()
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		if (m_spriteType == SpriteType::ChangeColor)
		{
			m_totalTime += delta * 30;
			float a = sinf(m_totalTime);
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto& pad = device.GetControlerVec()[0];

			if (pad.wPressedButtons & XINPUT_GAMEPAD_B && m_isChangeColorState == ChangeColorState::Wait)
			{
				m_isChangeColorState = ChangeColorState::ChangeColor;
			}

			if (m_isChangeColorState == ChangeColorState::ChangeColor)
			{
				auto drawComp = GetComponent<PCTSpriteDraw>();
				m_vertices[0].color = Col4(a, a, a, 1.0f);
				m_vertices[1].color = Col4(a, a, a, 1.0f);
				m_vertices[2].color = Col4(a, a, a, 1.0f);
				m_vertices[3].color = Col4(a, a, a, 1.0f);
				drawComp->UpdateVertices(m_vertices);
			}
		}

		if (m_spriteType == SpriteType::SeekSize)
		{
			m_totalTime += delta;

			if (m_totalTime > 5.0f && m_isSeekSizeState != SeekSizeState::Stop)
			{
				m_isSeekSizeState = SeekSizeState::SizeChange;
			}
			if (m_isSeekSizeState == SeekSizeState::SizeChange)
			{
				m_uiSizeCoefficient += 0.05f;
				switch (m_seekDirection)
				{
				case basecross::Sprites::SeekDirection::UpperLeft:
					m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient);
					m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient);
					m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					break;
				case basecross::Sprites::SeekDirection::UpperRight:
					m_vertices[0].position.x = (m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient;
					m_vertices[2].position.x = (m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient;
					m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					break;
				case basecross::Sprites::SeekDirection::BottomLeft:
					m_vertices[0].position.y = (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient);
					m_vertices[1].position.y = (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient);
					break;
				case basecross::Sprites::SeekDirection::BottomRight:
					m_vertices[0].position.x = (m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient;
					m_vertices[0].position.y = (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[1].position.y = (-m_spriteSize.y + m_afterSize.y) * m_uiSizeCoefficient;
					m_vertices[2].position.x = (m_spriteSize.x - m_afterSize.x) * m_uiSizeCoefficient;
					break;
				default:
					break;
				}

				auto drawComp = GetComponent<PCTSpriteDraw>();
				drawComp->UpdateVertices(m_vertices);

				if (m_uiSizeCoefficient > 1.0f)
				{
					m_isSeekSizeState = SeekSizeState::Stop;
				}
			}
		}

		if (m_spriteType == SpriteType::Fade)
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto& pad = device.GetControlerVec()[0];

			if (m_fadeType == FadeType::FadeIn)
			{
				m_alphaNum -= m_fadeSpeed;

				auto drawComp = GetComponent<PCTSpriteDraw>();
				drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
				drawComp->UpdateVertices(m_vertices);
			}
			if (m_fadeType == FadeType::FadeOut)
			{
				m_alphaNum += m_fadeSpeed;

				auto drawComp = GetComponent<PCTSpriteDraw>();
				drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
				drawComp->UpdateVertices(m_vertices);
			}
		}
	}

	void Sprites::CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey)
	{
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
		// 描画レイヤーを最前面に
		SetDrawLayer((int)DrawLayer::ForeFront);
	}

	void Sprites::CreateColorChangeSprite(const Vec3& position, const Vec2& size, const wstring& texKey)
	{
		m_spriteType = SpriteType::ChangeColor;
		CreateSprite(position, size, texKey);
	}

	void Sprites::CreateSeekSizeSprite(const Vec3& position, const Vec2& beforeSize, const Vec2& afterSize, const wstring& texKey, const int seekDirection)
	{
		m_spriteType = SpriteType::SeekSize;
		m_seekDirection = (SeekDirection)seekDirection;
		m_afterSize = afterSize;
		CreateSprite(position, beforeSize, texKey);
	}

	void Sprites::CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const int fadeType){

		m_spriteType = SpriteType::Fade;
		m_fadeType = (FadeType)fadeType;
		if (m_fadeType == FadeType::FadeOut) {
			m_alphaNum = 0.0f;
		}
		else if(m_fadeType == FadeType::FadeIn)
		{
			m_alphaNum = 1.0f;
		}

		CreateSprite(position, size, texKey);
	}
	
}