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
		const Vec2 m_DefaultSize; // 大きさ
		const Col4 m_SpriteColor; // 色

		// スプライトの数とずらすUV座標
		const float m_SpriteNumber;
		const float m_SpriteUvPosition;
		
		int m_number; // 表示される数字を表す値

		wstring m_spriteKey; // 使用するスプライトの名前

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// トランスフォームコンポーネントとドローコンポーネント
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public :
		// コンストラクタ
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey);
		// デストラクタ
		~NumberUI();

		// 初期化
		void OnCreate() override;

		// 表示する数字の設定
		void SetNumber(int number); 

		/**
		* 数字の表示位置を設定する関数
		*
		* @param pos 表示したい位置(Vec3型)
		* @param h Y座標の係数
		*/
		void SetPosition(const Vec3& pos, float h);

		/**
		* 数字の表示位置を設定する関数
		*
		* @param pos 表示したい位置(Vec2型)
		* @param h Y座標の係数
		*/
		void SetPosition(const Vec2& pos, float h);

		/**
		* 数字の表示位置を設定する関数
		*
		* @param x : 表示したいx座標
		* @param y : 表示したいy座標
		* @param h : Y座標の係数
		*/
		void SetPosition(float x, float y, float h);
	};
}