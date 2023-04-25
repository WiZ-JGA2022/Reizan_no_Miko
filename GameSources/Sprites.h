/*!
@file Sprites.h
@brief スプライトの親クラスの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		Vec2 m_spriteSize;
		Vec3 m_spritePosition;
		wstring m_textureKey;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public :
		Sprites(const shared_ptr<Stage>& stage);
		~Sprites();

		void OnCreate() override;

		void CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey);
	};
}