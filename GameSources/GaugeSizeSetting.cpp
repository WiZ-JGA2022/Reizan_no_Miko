/*!
@file GaugeSizeSettings.cpp
@brief 各種ゲージの頂点データなどの設定の実装
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GaugeSizeSettings::OnCreate()
	{
		// 頂点データの生成
		SetVartices();

		m_indices = {
			0, 1, 2, // 左上の三角(ポリゴン)
			2, 1, 3  // 右下の三角(ポリゴン)
		};

		// トランスフォームコンポーネントの取得
		m_transform = GetComponent<Transform>();
		// 見た目の設定
		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_TextureKey);

		// 描画レイヤーを設定
		SetDrawLayer((int)DrawLayer::ForeFront);
		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void GaugeSizeSettings::SetVartices()
	{
		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		// 頂点データの設定
		m_vertices = {
			{Vec3(0.0f			 , 0.0f			  , 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(m_DefaultSize.x, 0.0f			  , 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(0.0f			 ,-m_DefaultSize.y, 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(m_DefaultSize.x,-m_DefaultSize.y, 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};
	}

	void GaugeSizeSettings::UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize)
	{
		// 1ごとのゲージのサイズを計算
		float gaugeSizeDiff = m_DefaultSize.x / gaugeSizeLimit;

		// 頂点データを更新
		for (int i = 0; i < m_SquareVartex; i++)
		{
			// テクスチャ名がHPBAR_GREENまたはHPBAR_REDなら
			if (m_TextureKey == L"HPBAR_GREEN" || m_TextureKey == L"HPBAR_RED")
			{
				// 右側から減らす
				float currentLostGauge = gaugeSizeLimit - currentGaugeSize;

				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = m_DefaultSize.x - gaugeSizeDiff * currentLostGauge;
				}
			}
			else // そうでないなら
			{
				// 左側から増やす
				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = gaugeSizeDiff * currentGaugeSize;
				}				
			}
		}

		// 更新されたデータを元にポリゴンを作り直す
		m_draw->UpdateVertices(m_vertices);
		
	}

	void GaugeSizeSettings::SetPosition(const Vec3& pos, float h)
	{
		auto& app = App::GetApp();

		// 画面の幅と高さを取得する
		auto width = app->GetGameWidth();
		auto height = app->GetGameHeight();

		// 原点を画面左上にする。また、Y座標は下向きに反転させる
		m_transform->SetPosition(Vec3(-pos.x + (width * 0.5f), -pos.y + (height * h), pos.z));
	}

}