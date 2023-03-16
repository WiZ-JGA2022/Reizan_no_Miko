/*!
@file ExpBar.cpp
@brief 経験値を表示するバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		SetVartices(30.0f); // 引数をexpLimitにする

		m_indices = {
			0, 1, 2, // 左上の三角(ポリゴン)
			2, 1, 3  // 右下の三角(ポリゴン)
		};

		m_bar.reserve(30);

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"EXPBAR_BLUE");

		m_transform = GetComponent<Transform>();

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	// 更新処理 //
	void ExpBar::OnUpdate()
	{
		SetVartices(30.0f); // 引数をexpLimitにする

		for (int i = 0; i < 30; i++) // 繰り返す回数を取得したexpの数にする(int型にキャストする)
		{
			auto barObj = ObjectFactory::Create<ExpBar>(GetStage()); // オブジェクトを生成するけどステージに追加しない
			barObj->SetPosition(App::GetApp()->GetGameWidth() - m_expBarWidth * i, 0.0f); // 画面の左端から右端に向かってゲージを伸ばす
			barObj->SetUvPosition(i, 30.0f, 3); // 第二引数をexpLimitに、第三引数をexpLvにする
			m_bar.push_back(barObj); // オブジェクトを配列に追加
		}
	}

	// 描画処理 //
	void ExpBar::OnDraw()
	{
		for (auto& bar : m_bar)
		{
			bar->GameObject::OnDraw();
		}
	}

	// 表示するUV座標を指定する //
	void ExpBar::SetUvPosition(int number, float expLimit, int expLv)
	{
		m_uvPosition = number;

		// 頂点データを更新（UV座標を指定の位置にずらす）
		for (int i = 0; i < m_SquareVartex; i++)
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

	// ポリゴンの頂点位置を設定する関数 //
	void ExpBar::SetVartices(float expLimit)
	{
		m_expBarWidth = m_DefaultExpBarWidth / expLimit; // 1exp当たりのバーの大きさを計算

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		float u = m_uvPosition / 10.0f; // uvの位置を調整

		// 頂点データの設定
		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f), white, Vec2(u, 0.0f)}, // 左上
			{Vec3(m_expBarWidth, 0.0f, 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // 右上
			{Vec3(0.0f,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u, 1.0f)}, // 左下
			{Vec3(m_expBarWidth,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // 右下
		};
	}
	
	// 表示位置の設定 //
	void ExpBar::SetPosition(const Vec3& pos)
	{
		auto& app = App::GetApp();

		// 画面の幅と高さを取得する
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		m_transform->SetPosition(Vec3(-pos.x + (w * 0.5f), -pos.y + h * 0.46f, pos.z)); // 画面半分ずつずらして原点を画面左上にずらす。また、Y座標は下向きに反転させる
	}

}
//end basecross
