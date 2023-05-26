/*!
@file PlayerHpGauge.h
@brief プレイヤーのHPバー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerHpGauge :public GameObject
	{
		const Vec2 m_DefaultSize;
		const wstring m_TexKey;
		const float m_AddPosY;

		weak_ptr<PlayerStatusController> m_playerStatus;
		shared_ptr<PCTStaticDraw> m_draw;

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
		PlayerHpGauge(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<PlayerStatusController>& objectPtr,
			const wstring& texKey);
		virtual ~PlayerHpGauge();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;

		void UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize);
	};

}