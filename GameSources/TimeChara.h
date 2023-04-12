/**
@file TimeChara.h
@brief 文字の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeChara : public GameObject {
		const Vec2 m_UiSize = Vec2(128.0f, 25.6f);

		Vec3 m_position;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public :
		TimeChara(const shared_ptr<Stage>& stage);
		~TimeChara();

		void OnCreate();
	};
}