/*!
@file PlayerHpGauge.cpp
@brief プレイヤーのHPバーの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築と破棄
	PlayerHpGauge::PlayerHpGauge(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<PlayerStatusController>& objectPtr,
		const wstring& texKey) :
		GameObject(StagePtr),
		m_AddPosY(1.5f),
		m_DefaultSize(Vec2(1.0f, 0.25f)),
		m_TexKey(texKey),
		m_playerStatus(objectPtr)
	{}
	PlayerHpGauge::~PlayerHpGauge() {}

	//初期化
	void PlayerHpGauge::OnCreate() {

		auto transform = GetComponent<Transform>();
		if (!m_playerStatus.expired()) {
			auto playerStatusPtr = m_playerStatus.lock();
			auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
			auto position = playerTrans->GetPosition();
			position.y += m_AddPosY;
			transform->SetPosition(position);
			transform->SetScale(1.0f, 1.0f, 1.0f);
			transform->SetQuaternion(playerTrans->GetQuaternion());

			const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

			m_vertices = {
				{Vec3(-m_DefaultSize.x * 0.5f, 0.0f			   , 0.0f), white, Vec2(0.0f, 0.0f)},
				{Vec3(m_DefaultSize.x * 0.5f , 0.0f			   , 0.0f), white, Vec2(0.1f, 0.0f)},
				{Vec3(-m_DefaultSize.x * 0.5f, -m_DefaultSize.y, 0.0f), white, Vec2(0.0f, 1.0f)},
				{Vec3(m_DefaultSize.x * 0.5f , -m_DefaultSize.y, 0.0f), white, Vec2(0.1f, 1.0f)},
			};
			m_indices = {
				0, 1, 2,
				2, 1, 3
			};

			m_draw = AddComponent<PCTStaticDraw>();
			m_draw->SetOriginalMeshUse(true);
			m_draw->CreateOriginalMesh(m_vertices, m_indices);
			m_draw->SetTextureResource(m_TexKey);
			SetAlphaActive(true);
			if (m_TexKey == L"HPBAR_GREEN")
			{
				SetDrawLayer((int)DrawLayer::Bottom);
			}
			else if (m_TexKey == L"HPBAR_RED")
			{
				SetDrawLayer((int)DrawLayer::MostBottom);
			}
		}

	}

	void PlayerHpGauge::OnUpdate() {

		if (!m_playerStatus.expired()) {

			auto transform = GetComponent<Transform>();
			auto playerStatusPtr = m_playerStatus.lock();
			auto cameraPtr = GetStage()->GetView()->GetTargetCamera();
			auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
			auto position = playerTrans->GetPosition();
			position.y += m_AddPosY;
			transform->SetPosition(position);

			//向きをビルボードにする
			Quat Qt;
			Qt = Billboard(cameraPtr->GetAt() - cameraPtr->GetEye());
			transform->SetQuaternion(Qt);

			if (m_TexKey == L"HPBAR_GREEN")
			{
				if (!(playerStatusPtr->GetStatusValue(L"HP") < 0.0f))
				{
					// ゲージの大きさを更新
					UpdateGaugeSize(playerStatusPtr->GetMaxHp(), playerStatusPtr->GetStatusValue(L"HP"));
				}
			}
			else if (m_TexKey == L"HPBAR_RED")
			{
				UpdateGaugeSize(playerStatusPtr->GetMaxHp(), (float)playerStatusPtr->GetMaxHp());
			}
		}
	}

	void PlayerHpGauge::UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize)
	{
		float gaugeSizeDiff = m_DefaultSize.x / gaugeSizeLimit;
		for (int i = 0; i < 4; i++)
		{
			float currentLostGauge = gaugeSizeLimit - currentGaugeSize;
			if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
			{
				m_vertices[i].position.x = m_DefaultSize.x * 0.5f - (gaugeSizeDiff * currentLostGauge);
			}
		}

		m_draw->UpdateVertices(m_vertices);
	}


}