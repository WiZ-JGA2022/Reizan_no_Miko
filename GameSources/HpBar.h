/* !
@file HpBar.h
@brief プレイヤーの体力を表示するバー
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class HpBar : public GameObject
	{
		// HpBarの初期サイズ
		const float m_DefaultHpBarWidth;
		const float m_DefaultHpBarHeight;
		// 頂点の数
		const int m_SquareVartex;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// BarのUV座標を指定する配列
		vector<shared_ptr<HpBar>> m_bar;

		int m_uvPosition; // 表示される位置を表す値
		float m_HpBarWidth; // 1Hp毎に伸ばすHpBarの横幅
		float m_uvShiftDistance;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		HpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultHpBarWidth(400.0f),
			m_DefaultHpBarHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(0),
			m_HpBarWidth(0),
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
		void SetUvPosition(int number, float HpLimit, int HpLv);

		// ポリゴンの頂点位置を設定する関数 //
		void SetVartices(float HpLimit);

		// 2D座標指定でスプライトの位置を設定する関数 //
		virtual void SetPosition(const Vec3& pos);

		// 2D座標指定でスプライトの位置を設定する関数（Vec2バージョン）
		virtual void SetPosition(const Vec2& pos)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f));
		}

		void SetPosition(float x, float y)
		{
			SetPosition(Vec2(x, y));
		}

	};
}
//end basecross

