/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		m_expBarWidth = m_DefaultExpBarWidth / 30; // 320.0fはExpBar全体の大きさに 30をMAXEXPに
		m_bar.reserve(30);

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

		float u = m_uvPosition / 10.0f;

		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f), white, Vec2(u, 0.0f)}, // 左上
			{Vec3(m_expBarWidth, 0.0f, 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // 右上
			{Vec3(0.0f,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u, 1.0f)}, // 左下
			{Vec3(m_expBarWidth,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2, // 左上の三角(ポリゴン)
			2, 1, 3  // 右下の三角(ポリゴン)
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"EXPBAR_BLUE");

		m_transform = GetComponent<Transform>();

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void ExpBar::OnUpdate()
	{
		for (int i = 0; i < 30; i++)
		{
			auto barObj = ObjectFactory::Create<ExpBar>(GetStage()); // オブジェクトを生成するけどステージに追加しない
			barObj->SetPosition(App::GetApp()->GetGameWidth() - m_expBarWidth * i, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
			barObj->SetUvPosition(i, 30.0f, 3);
			m_bar.push_back(barObj);
		}
	}

	void ExpBar::OnDraw()
	{
		for (auto& bar : m_bar)
		{
			bar->GameObject::OnDraw();
		}
	}

	// 表示するUV座標を指定する
	void ExpBar::SetUvPosition(int number, float expLimit, int expLv)
	{
		m_uvPosition = number;

		// 頂点データを更新（UV座標を指定の位置にずらす）
		for (int i = 0; i < 4; i++)
		{
			if (i % 2 == 0)
			{
				m_vertices[i].textureCoordinate.x = m_uvPosition / expLimit;
			}
			else
			{
				m_vertices[i].textureCoordinate.x = m_uvPosition / expLimit + (m_uvShiftDistance / expLv);
			}
		}

		// 更新されたデータを元にポリゴンを作り直す
		m_draw->UpdateVertices(m_vertices);
	}
	
	void ExpBar::SetPosition(const Vec3& pos)
	{
		auto& app = App::GetApp();

		// 画面の幅と高さを取得する
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		m_transform->SetPosition(Vec3(-pos.x + (w * 0.5f), -pos.y + h * 0.5f, pos.z)); // 画面半分ずつずらして原点を画面左上にずらす。また、Y座標は下向きに反転させる
	}

}
//end basecross
