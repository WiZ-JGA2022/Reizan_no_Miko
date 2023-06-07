/*!
@file PlayerHpGauge.h
@brief プレイヤーのHPバー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerHpGauge :public GameObject
	{
		const Vec2 m_DefaultSize; // PlayerHpGaugeの初期サイズ
		const wstring m_TexKey; // テクスチャキー
		const float m_AddPosY; // PlayerHpGaugeのpos
		
		// ドローコンポーネントとトランスフォームコンポーネントを取得
		weak_ptr<PlayerStatusController> m_playerStatus;
		shared_ptr<PCTStaticDraw> m_draw;
		
		// スプライトの元になる頂点データと頂点インデックス
		vector<VertexPositionNormalTexture> m_vertices;
		vector<uint16_t> m_indices;

		Quat Billboard(const Vec3& Line) {
			Vec3 temp = Line;
			Mat4x4 rotMatrix;
			Vec3 defUp(0, 1.0f, 0);
			Vec2 tempVec2(temp.x, temp.z);
			if (tempVec2.length() < 0.1f) {
				defUp = Vec3(0, 0, 1.0f);
			}
			temp.normalize();
			rotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), temp, defUp);
			rotMatrix.inverse();
			Quat qt;
			qt = rotMatrix.quatInMatrix();
			qt.normalize();
			return qt;
		}


	public:
		// コンストラクタ
		PlayerHpGauge(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<PlayerStatusController>& objectPtr,
			const wstring& texKey);
		// デストラクタ
		virtual ~PlayerHpGauge();
		// 初期化
		virtual void OnCreate() override;
		// 更新処理
		virtual void OnUpdate() override;
		// Gaugeの更新処理
		void UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize);
	};

}