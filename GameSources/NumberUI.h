/**
@file NumberUI.h
@brief 各種パラメータに使用する数字の実装
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class NumberUI : public Sprites {
		// 大きさ
		const Vec2 m_DefaultSize;
		// 色
		const Col4 m_SpriteColor;
		// スプライトの数とずらすUV座標
		const float m_SpriteNumber = 11.0f;
		const float m_SpriteUvPosition = 0.09f;

		// 表示される数字を表す値
		int m_number;

		// 使用するスプライトの名前
		wstring m_spriteKey;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// 頻繁に使用するコンポーネントを持たせてアクセスしやすくする
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public :
		// コンストラクタ
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey);
		// デストラクタ
		~NumberUI();

		void OnCreate() override; // 初期化
		
		void SetNumber(int number); // 

		void SetPosition(const Vec3& pos, float h); //
		void SetPosition(const Vec2& pos, float h); //
		void SetPosition(float x, float y, float h); //
	};
}