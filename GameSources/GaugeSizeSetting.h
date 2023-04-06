/* !
@file GaugeSizeSettings.h
@brief 各種ゲージの頂点データなどの設定
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GaugeSizeSettings : public GameObject 
	{
		// Gaugeの初期サイズ
		const float m_DefaultGaugeWidth;
		const float m_DefaultGaugeHeight;
		// 頂点の数
		const int m_SquareVartex;

		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// ドローコンポーネントとトランスフォームコンポーネントを取得
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

		int m_uvPosition; // 表示される位置を表す値
		float m_gaugeWidth; // 一単位毎に伸ばす・減らすゲージの横幅
		float m_uvShiftDistance; // 1ゲージごとにずらすUV座標の差

		bool m_isHp; // HPバー用の処理かEXPバー用の処理か判定する

	public:
		/**
		* GaugeSizeSettingsのコンストラクタ
		*
		* @param defaultGaugeWidth : 初期状態でのゲージの横幅
		* @param isHp : HPバーで使うならtrue それ以外ならfalse
		*/
		GaugeSizeSettings(const std::shared_ptr<Stage>& stage, float defaultGaugeWidth, bool isHp) :
			GameObject(stage),
			m_DefaultGaugeWidth(defaultGaugeWidth),
			m_DefaultGaugeHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(1),
			m_gaugeWidth(0),
			m_uvShiftDistance(0.1f),
			m_isHp(isHp)
		{
		}
		// 初期化 
		void OnCreate() override;

		/**
		* ゲージの大きさを更新する関数
		*
		* @param gaugeSizeLimit HPまたはEXPの上限
		* @param currentGaugeSize 現在のHPまたはEXPの数
		*/
		void UpdateGaugeSize(float gaugeSizeLimit, float currentGaugeSize);

		/**
		* ゲージの頂点データを設定する関数
		*/
		void SetVartices();

		/**
		* ゲージの表示位置を設定する関数
		*
		* @param pos 表示したい位置(Vec3型)
		* @param h Y座標の係数
		*/
		virtual void SetPosition(const Vec3& pos, float h);

		/**
		* ゲージの表示位置を設定する関数
		*
		* @param pos 表示したい位置(Vec2型)
		* @param h Y座標の係数
		*/
		virtual void SetPosition(const Vec2& pos, float h)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f), h);
		}

		/**
		* ゲージの表示位置を設定する関数
		*
		* @param pos : 表示したい位置(float型)
		* @param h : Y座標の係数
		*/
		void SetPosition(float x, float y, float h)
		{
			SetPosition(Vec2(x, y), h);
		}

		/**
		* ゲージの横幅を取得する関数
		*
		* @return ゲージの横幅
		*/
		float GetGaugeSize()
		{
			return m_gaugeWidth;
		}
	};
}