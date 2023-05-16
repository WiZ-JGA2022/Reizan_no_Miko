

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