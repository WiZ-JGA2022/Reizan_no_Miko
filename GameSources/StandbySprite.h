/**
@file StandbySprite.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StandbySprite : public GameObject {
		const Vec2 m_UiSize = Vec2(384.0f, 64.0f);

		Vec3 m_position;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public:
		StandbySprite(const shared_ptr<Stage>& stage);
		~StandbySprite();

		void OnCreate();
	};
}