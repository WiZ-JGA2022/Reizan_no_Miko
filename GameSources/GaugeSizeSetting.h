/* !
@file GaugeSizeSetting.h
@brief 各種ゲージの頂点データなどの設定
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class GaugeSizeSetting : public GameObject 
	{
		// HpBarの初期サイズ
		const float m_DefaultGaugeWidth;
		const float m_DefaultGaugeHeight;
		// 頂点の数
		const int m_SquareVartex;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

		int m_uvPosition; // 表示される位置を表す値
		float m_gaugeWidth; // 一単位毎に伸ばす・減らすゲージの横幅

	public:
		// コンストラクタ //
		GaugeSizeSetting(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultGaugeWidth(400.0f),
			m_DefaultGaugeHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(0),
			m_gaugeWidth(0)
		{
		}
		// 初期化 //
		void OnCreate() override;

		// UVの場所を決める関数 //
		void SetGaugeSize(float gaugeSizeLimit, float currentGaugeSize);

		// 2D座標指定でスプライトの位置を設定する関数 //
		virtual void SetPosition(const Vec3& pos, float h);

		// 2D座標指定でスプライトの位置を設定する関数（Vec2バージョン）//
		virtual void SetPosition(const Vec2& pos, float h)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f), h);
		}

		// 2D座標指定でスプライトの位置を設定する関数（floatバージョン）//
		void SetPosition(float x, float y, float h)
		{
			SetPosition(Vec2(x, y), h);
		}
	};
}