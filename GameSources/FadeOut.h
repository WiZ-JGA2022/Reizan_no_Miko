/* !
@file FadeOut.h
@brief フェードアウトの定義
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class FadeOut : public Sprites {
		const Vec2 m_DefaultSize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		FadeOut(const shared_ptr<Stage>& stage);
		~FadeOut();

		void OnCreate() override;
	};
}

