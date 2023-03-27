/*!
@file GaugeSizeSettings.cpp
@brief 各種ゲージの頂点データなどの設定の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GaugeSizeSettings::OnCreate()
	{
		SetVartices();

		m_indices = {
			0, 1, 2, // 左上の三角(ポリゴン)
			2, 1, 3  // 右下の三角(ポリゴン)
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		if (m_isHp)
		{
			m_draw->SetTextureResource(L"HPBAR_GREEN");
		}
		else
		{
			m_draw->SetTextureResource(L"EXPBAR_BLUE");
		}

		m_transform = GetComponent<Transform>();

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void GaugeSizeSettings::SetVartices()
	{
		m_gaugeWidth = m_DefaultGaugeWidth; // 1exp当たりのバーの大きさを計算

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		float u = m_uvPosition / 10.0f; // uvの位置を調整

		// 頂点データの設定
		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f), white, Vec2(u, 0.0f)}, // 左上
			{Vec3(m_gaugeWidth, 0.0f, 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // 右上
			{Vec3(0.0f,-m_DefaultGaugeHeight, 0.0f), white, Vec2(u, 1.0f)}, // 左下
			{Vec3(m_gaugeWidth,-m_DefaultGaugeHeight, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // 右下
		};
	}

	void GaugeSizeSettings::UpdateGaugeSize(float gaugeSizeLimit, float currentGaugeSize)
	{
		float gaugeSizeDiff = m_DefaultGaugeWidth / gaugeSizeLimit;

		// 頂点データを更新
		for (int i = 0; i < m_SquareVartex; i++)
		{
			if (m_isHp)
			{
				float currentLostGauge = gaugeSizeLimit - currentGaugeSize;

				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = m_DefaultGaugeWidth - gaugeSizeDiff * currentLostGauge;
				}
			}
			else
			{
				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = gaugeSizeDiff * currentGaugeSize;
				}				
			}

			//if (i % 2 == 0)
			//{
			//	m_vertices[i].textureCoordinate.x = m_uvPosition / gaugeSizeLimit;
			//}
			//else
			//{
			//	m_vertices[i].textureCoordinate.x = m_uvPosition / gaugeSizeLimit + (m_uvShiftDistance / statusLevel);
			//}
		}

		// 更新されたデータを元にポリゴンを作り直す
		m_draw->UpdateVertices(m_vertices);
	

		// デバッグ用文字列 //
		//auto& app = App::GetApp();
		//wstringstream wss;
		//auto scene = app->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());
		// ここまで //
	}

	void GaugeSizeSettings::SetPosition(const Vec3& pos, float h)
	{
		auto& app = App::GetApp();

		// 画面の幅と高さを取得する
		auto width = app->GetGameWidth();
		auto height = app->GetGameHeight();

		m_transform->SetPosition(Vec3(-pos.x + (width * 0.5f), -pos.y + (height * h), pos.z)); // 画面半分ずつずらして原点を画面左上にずらす。また、Y座標は下向きに反転させる
	}

}