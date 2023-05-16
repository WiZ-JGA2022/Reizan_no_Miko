/*!
@file Sprites.h
@brief スプライトの親クラスの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		enum class SpriteType {
			Normal,			// 通常
			ChangeColor,	// 色が変わる
			SeekSize,		// サイズが変わる
			Fade			// フェード処理
		};

		enum class FadeType {
			None,		// 何もしない
			FadeOut,	// フェードアウト
			FadeIn		// フェードイン
		};

		enum class SeekSizeState
		{
			Wait,		// 待機
			Stop,		// 終了
			SizeChange	// 実行
		};

		enum class ChangeColorState {
			Wait,		// 待機
			ChangeColor	// 実行
		};

		enum SpriteType m_spriteType = SpriteType::Normal;
		enum FadeType m_fadeType = FadeType::None;
		enum SeekSizeState m_isSeekSizeState = SeekSizeState::Wait;
		enum ChangeColorState m_isChangeColorState = ChangeColorState::Wait;

		Vec2 m_spriteSize;	// 大きさ
		Vec2 m_afterSize;	// サイズ変更後の大きさ

		float m_uiSizeCoefficient;	// UIサイズの係数
		float m_totalTime;			// 時間

		float m_alphaNum;	// 透明度
		float m_fadeSpeed;	// フェードの速度

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

		/**
		* スプライトを作成する関数
		* 
		* @param position 表示位置
		* @param size 表示サイズ
		* @param texKey 使用テクスチャ
		*/
		void CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* 色が変わるスプライトを作成する関数
		*
		* @param position 表示位置
		* @param size 表示サイズ
		* @param texKey 使用テクスチャ
		*/		
		void CreateColorChangeSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* サイズが変わるスプライトを作成する関数
		*
		* @param position 表示位置
		* @param beforeSize 初期表示サイズ
		* @param afterSize 変更後表示サイズ
		* @param texKey 使用テクスチャ
		*/
		void CreateSeekSizeSprite(const Vec3& position, const Vec2& beforeSize, const Vec2& afterSize, const wstring& texKey);

		/**
		* フェードするスプライトを作成する関数
		*
		* @param position 表示位置
		* @param size 表示サイズ
		* @param texKey 使用テクスチャ
		* @param fadeType 1:フェードアウト 2:フェードイン
		*/
		void CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const int fadeType);
	};
}