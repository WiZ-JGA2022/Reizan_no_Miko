

/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class KeyStoneGauge :public GameObject
	{
		const Vec2 m_DefaultSize = Vec2(5.0f, 0.5f);

		weak_ptr<KeyStone> m_keyStoneHp;
		shared_ptr<PCTStaticDraw> m_draw;

		vector< VertexPositionNormalTexture> m_vertices;
		vector<uint16_t> m_indices;

		

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}


	public:
		KeyStoneGauge(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<KeyStone>& SeekObjectPtr);
		virtual ~KeyStoneGauge();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;

		void UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize);
	};

}