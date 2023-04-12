/*!
@file AttackAnnounce.h
@brief 攻撃予告スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class AttackAnnounceCircle : public GameObject {
		const Vec2 m_DefaultSize = Vec2(160.0f, 160.0f);

		Vec3 m_position;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public :
		AttackAnnounceCircle(const shared_ptr<Stage>& stage, const Vec3& position);
		~AttackAnnounceCircle();

		void OnCreate() override;
		void OnUpdate() override;
	};

	class AttackAnnounceLine : public GameObject {
		const Vec3 m_DefaultSize = Vec3(160.0f, 0.1f, 160.0f);

		Vec3 m_position;
		Vec3 m_scale;

		float m_coefficient;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PNTStaticDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public:
		AttackAnnounceLine(const shared_ptr<Stage>& stage, const Vec3& position);
		~AttackAnnounceLine();

		void OnCreate() override;
		void OnUpdate() override;
	};
}