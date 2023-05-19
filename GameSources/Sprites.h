/*!
@file Sprites.h
@brief スプライトの親クラスの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		Vec2 m_spriteSize;	// 大きさ
		Vec2 m_afterSize;	// サイズ変更後の大きさ
		Vec3 m_position;	// UIの位置

		float m_uiSizeCoefficient;	// UIサイズの係数
		float m_totalTime;			// 時間
		float m_waitSecond;			// サイズ変化までの待機時間

		float m_alphaNum;	// 透明度
		float m_fadeSpeed;	// フェードの速度

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	protected :
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
		enum class SeekType {
			UpperLeft,	// 左上
			GameSprite,	// 右上に動きながら縮小
			BottomLeft,	// 左下
			BottomRight	// 右下
		};

		enum class ChangeColorState {
			Wait,		// 待機
			ChangeColor	// 実行
		};

		enum SpriteType m_spriteType = SpriteType::Normal; // スプライトタイプ
		enum FadeType m_fadeType = FadeType::None; // フェードタイプ
		enum SeekSizeState m_isSeekSizeState = SeekSizeState::Wait; // サイズ変更の状態
		enum SeekType m_seekType = SeekType::BottomRight; // 変化する方向
		enum ChangeColorState m_isChangeColorState = ChangeColorState::Wait; // 色変更の状態

	public:
		Sprites(const shared_ptr<Stage>& stage);
		~Sprites();

		void OnCreate() override;
		void OnUpdate() override;

		/**
		* スプライトを作成する関数
		* 
		* @param position	表示位置
		* @param size		表示サイズ
		* @param texKey		使用テクスチャ
		*/
		void CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* 色が変わるスプライトを作成する関数
		*
		* @param position	表示位置
		* @param size		表示サイズ
		* @param texKey		使用テクスチャ
		*/		
		void CreateColorChangeSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* サイズが変わるスプライトを作成する関数
		*
		* @param position	表示位置
		* @param beforeSize 初期表示サイズ
		* @param afterSize	変更後表示サイズ
		* @param texKey		使用テクスチャ
		* @param seekType	サイズ変更タイプ
		* @param waitSecond サイズ変更までの待機時間
		*/
		void CreateSeekSizeSprite(const Vec3& position, const Vec2& beforeSize, const Vec2& afterSize, const wstring& texKey, const SeekType& seekType, const float waitSecond);

		/**
		* フェードするスプライトを作成する関数
		*
		* @param position	表示位置
		* @param size		表示サイズ
		* @param texKey		使用テクスチャ
		* @param fadeType	フェードタイプ
		*/
		void CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType);
	};
}