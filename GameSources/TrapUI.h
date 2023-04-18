/* !
@file TrapUI.h
@brief トラップUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class TrapSprite : public GameObject {
		const Vec2 m_DefaultSize = Vec2(150.0f, 150.0f);;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		TrapSprite(const shared_ptr<Stage>& stage);
		~TrapSprite();

		void OnCreate() override;
	};
}