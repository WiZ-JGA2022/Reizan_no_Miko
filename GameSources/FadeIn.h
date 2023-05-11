/*!
@file FadeIn.cpp
@brief フェードインの定義
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeIn : public Sprites {
		const Vec2 m_DefaultSize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		FadeIn(const shared_ptr<Stage>& stage);
		~FadeIn();

		void OnCreate() override;
	};
}
