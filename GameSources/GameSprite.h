/**
@file GameSprite.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class GameSprite : public Sprites {
		const Vec2 m_DefaultSize = Vec2(384.0f, 64.0f);

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public:
		GameSprite(const shared_ptr<Stage>& stage);
		~GameSprite();

		void OnCreate();
	};
}