/*!
@file Sprites.h
@brief スプライトの親クラスの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		Vec2 m_spriteSize;

		float m_tutorialUiSize = 0.0f;
		float m_TotalTime;

		bool m_Trace;
		bool m_selected;
		bool m_changeSize;

		enum class TutorialState
		{
			Wait,		// 待機
			Stop,		// 実行
			SizeChange	// 実行遅延
		};
		enum TutorialState m_isState = TutorialState::Wait;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		Sprites(const shared_ptr<Stage>& stage);
		~Sprites();

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey, bool Trace, bool changeSize);
	};
}