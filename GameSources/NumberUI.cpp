/**
@file NumberUI.cpp
@brief 各種パラメータに使用する数字の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NumberUI::NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey) :
		GameObject(stage),
		m_SpriteWidth(spriteSize.x),
		m_SpriteHeight(spriteSize.y),
		m_SpriteColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_spriteKey(spriteKey),
		m_number(0)
	{
	}
	NumberUI::~NumberUI() {}

	void NumberUI::OnCreate()
	{
		float uv = m_number / m_SpriteNumber;

		m_vertices = {
			{Vec3(0.0f			, 0.0f			, 0.0f), m_SpriteColor, Vec2(uv						, 0.0f)}, // 左上
			{Vec3(m_SpriteWidth	, 0.0f			, 0.0f), m_SpriteColor, Vec2(uv + m_SpriteUvPosition, 0.0f)}, // 右上
			{Vec3(0.0f			,-m_SpriteHeight, 0.0f), m_SpriteColor, Vec2(uv						, 1.0f)}, // 左下
			{Vec3(m_SpriteWidth	,-m_SpriteHeight, 0.0f), m_SpriteColor, Vec2(uv + m_SpriteUvPosition, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2, // 左上の三角(ポリゴン)
			2, 1, 3  // 右下の三角(ポリゴン)
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_spriteKey);

		m_transform = GetComponent<Transform>();

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void NumberUI::SetNumber(int number)
	{
		m_number = number;

		// 頂点データを更新（UV座標を指定のナンバーの位置にずらす）
		m_vertices[0].textureCoordinate.x = m_number / m_SpriteNumber;						// 左上
		m_vertices[1].textureCoordinate.x = m_number / m_SpriteNumber + m_SpriteUvPosition; // 右上
		m_vertices[2].textureCoordinate.x = m_number / m_SpriteNumber;						// 左下
		m_vertices[3].textureCoordinate.x = m_number / m_SpriteNumber + m_SpriteUvPosition;	// 右下

		// 更新されたデータを元にポリゴンを作り直す
		m_draw->UpdateVertices(m_vertices);
	}

	void NumberUI::SetPosition(const Vec3& pos)
	{
		auto& app = App::GetApp();

		// 画面の幅と高さを取得する
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		m_transform->SetPosition(Vec3(pos.x - (w * 0.5f), -pos.y + h * 0.5f, pos.z));
	}

	void NumberUI::SetPosition(const Vec2& pos)
	{
		SetPosition(Vec3(pos.x, pos.y, 0.0f));
	}

	void NumberUI::SetPosition(float x, float y)
	{
		SetPosition(Vec2(x, y));
	}

}