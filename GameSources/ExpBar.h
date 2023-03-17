/* !
@file ExpBar.h
@brief 経験値を表示するバー
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	class ExpBar : public GameObject
	{
		// ExpBarの初期サイズ
		const float m_DefaultExpBarWidth;
		const float m_DefaultExpBarHeight;
		// 頂点の数
		const int m_SquareVartex;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// BarのUV座標を指定する配列
		vector<shared_ptr<ExpBar>> m_bar;

		int m_uvPosition; // 表示される位置を表す値
		float m_expBarWidth; // 1Exp毎に伸ばすExpBarの横幅
		float m_uvShiftDistance;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		ExpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultExpBarWidth(200.0f),
			m_DefaultExpBarHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(0),
			m_expBarWidth(0),
			m_uvShiftDistance(0.1f)
		{
		}

		// 初期化 //
		void OnCreate() override;
		// 更新処理 //
		void OnUpdate() override;
		// 描画処理 //
		void OnDraw() override;

		// UVの場所を決める関数 //
		void SetUvPosition(int number, float expLimit, int expLv);

		// ポリゴンの頂点位置を設定する関数 //
		void SetVartices(float expLimit);

		// 2D座標指定でスプライトの位置を設定する関数 //
		virtual void SetPosition(const Vec3& pos);

		// 2D座標指定でスプライトの位置を設定する関数（Vec2バージョン）//
		virtual void SetPosition(const Vec2& pos)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f));
		}

		// 2D座標指定でスプライトの位置を設定する関数（floatバージョン）//
		void SetPosition(float x, float y)
		{
			SetPosition(Vec2(x, y));
		}

	};
}
//end basecross
