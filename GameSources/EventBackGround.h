/* !
@file EventBackGround.h
@brief LevelUpEvent実行中の背景
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EventBackGround : public GameObject {
		const Vec2 m_DefaultSize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	
	public :
		EventBackGround(const shared_ptr<Stage>& stage);
		~EventBackGround();

		void OnCreate() override;
		void OnUpdate() override;
	};
}