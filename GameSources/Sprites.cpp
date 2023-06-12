/*!
@file Sprites.cpp
@brief スプライトの親クラスの実装
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	Sprites::Sprites(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_spriteSize(Vec2(0.0f)),
		m_afterSize(Vec2(0.0f)),
		m_position(Vec3(0.0f)),
		m_uiSizeCoefficient(0.0f),
		m_totalTime(0.0f),
		m_waitSecond(5.0f),
		m_alphaNum(0.0f),
		m_fadeSpeed(0.01f)
	{
	}
	// デストラクタ
	Sprites::~Sprites() {}

	void Sprites::CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey)
	{
		m_position = position;
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
		m_draw->SetTextureResource(texKey);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		// 透過処理を有効にする
		SetAlphaActive(true);
		// 描画レイヤーを最前面に
		SetDrawLayer((int)DrawLayer::ForeFront);
	}

	void Sprites::CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType) {

		m_fadeType = fadeType;
		if (m_fadeType == FadeType::FadeIn) {
			m_alphaNum = 1.0f;
		}
		else if (m_fadeType == FadeType::FadeOut)
		{
			m_alphaNum = 0.0f;
		}

		CreateSprite(position, size, texKey);
	}

	void Sprites::UpdateFlashingSprite(const int flashSpeed)
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		float a = sinf(m_totalTime);
		if (a < 0.0f)
		{
			a *= -1;
		}

		m_totalTime += delta * flashSpeed; // 緩やかに変化する

		auto drawComp = GetComponent<PCTSpriteDraw>();
		m_vertices[0].color = Col4(a, a, a, 1.0f);
		m_vertices[1].color = Col4(a, a, a, 1.0f);
		m_vertices[2].color = Col4(a, a, a, 1.0f);
		m_vertices[3].color = Col4(a, a, a, 1.0f);
		drawComp->UpdateVertices(m_vertices);
	}

	void Sprites::UpdateFlashingSprite(const int flashSpeed, const int afterFlashSpeed, const bool speedChangeTrigger)
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();	// 時間の取得
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		float a = sinf(m_totalTime);
		if (a < 0.0f)
		{
			a *= -1;
		}

		if (m_isChangeColorState == ChangeColorState::DefaultSpeed)
		{
			m_totalTime += delta * flashSpeed; // 緩やかに変化する

			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(a, a, a, 1.0f);
			m_vertices[1].color = Col4(a, a, a, 1.0f);
			m_vertices[2].color = Col4(a, a, a, 1.0f);
			m_vertices[3].color = Col4(a, a, a, 1.0f);
			drawComp->UpdateVertices(m_vertices);

			if (speedChangeTrigger)
			{
				m_isChangeColorState = ChangeColorState::SpeedChange;
			}
		}

		if (m_isChangeColorState == ChangeColorState::SpeedChange)
		{
			m_totalTime += delta * afterFlashSpeed; // 素早く変化する

			auto drawComp = GetComponent<PCTSpriteDraw>();
			m_vertices[0].color = Col4(a, a, a, 1.0f);
			m_vertices[1].color = Col4(a, a, a, 1.0f);
			m_vertices[2].color = Col4(a, a, a, 1.0f);
			m_vertices[3].color = Col4(a, a, a, 1.0f);
			drawComp->UpdateVertices(m_vertices);
		}
		
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, const float seekSecond, const SeekType& seekType)
	{

		if (m_isSeekSizeState != SeekSizeState::Stop)
		{
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			// 時間の取得
			auto& app = App::GetApp();
			auto delta = app->GetElapsedTime();

			m_uiSizeCoefficient += delta / seekSecond;
			switch (seekType)
			{
			case SeekType::UpperLeft:
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::UpperRight:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft:
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				break;

			default:
				break;
			}

			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(m_vertices);
			if (m_uiSizeCoefficient > 1.0f)
			{
				m_uiSizeCoefficient = 1.0f;
			}

		}
	}

	void Sprites::UpdateSeekSizeSprite(const Vec2& afterSize, const float seekSecond, const SeekType& seekType, const float waitSecond)
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_totalTime += delta;

		if (m_totalTime > waitSecond && m_isSeekSizeState != SeekSizeState::Stop)
		{
			m_isSeekSizeState = SeekSizeState::SizeChange;
		}
		if (m_isSeekSizeState == SeekSizeState::SizeChange)
		{
			m_uiSizeCoefficient += delta / seekSecond;
			switch (seekType)
			{
			case SeekType::UpperLeft:
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				break;

			case SeekType::GameSprite:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[2].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.y = -m_spriteSize.y - (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;

				m_position.x = m_position.x - (m_position.x + 600.0f) * m_uiSizeCoefficient;
				m_position.y = m_position.y - (m_position.y - 400.0f) * (m_uiSizeCoefficient * 0.3f);
				m_transform->SetPosition(m_position);
				break;

			case SeekType::BottomLeft:
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[3].position.x = m_spriteSize.x - ((m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient);
				break;

			case SeekType::BottomRight:
				m_vertices[0].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
				m_vertices[0].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[1].position.y = (-m_spriteSize.y + afterSize.y) * m_uiSizeCoefficient;
				m_vertices[2].position.x = (m_spriteSize.x - afterSize.x) * m_uiSizeCoefficient;
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

	void Sprites::UpdateFadeSprite(const float fadeSecond)
	{
		// 時間の取得
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		if (m_fadeType == FadeType::FadeIn)
		{
			m_alphaNum -= delta / fadeSecond;

			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
			drawComp->UpdateVertices(m_vertices);
		}
		else if (m_fadeType == FadeType::FadeOut)
		{
			m_alphaNum += delta / fadeSecond;

			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, m_alphaNum));
			drawComp->UpdateVertices(m_vertices);
		}
	}
}