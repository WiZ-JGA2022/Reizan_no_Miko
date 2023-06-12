/*!
@file PlayerHpGauge.cpp
@brief プレイヤーのHPバーの実装
@prod 矢吹悠葉
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

	void PlayerHpGauge::OnCreate() {

		// トランスフォームコンポーネントの取得
		auto transform = GetComponent<Transform>();
		if (!m_playerStatus.expired()) {
			// プレイヤーステータスの取得
			auto playerStatusPtr = m_playerStatus.lock();
			// プレイヤーのトランスフォームを取得
			auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
			// プレイヤーの位置を取得
			auto position = playerTrans->GetPosition();
			// y方向にずらす
			position.y += m_AddPosY;
			// トランスフォームの設定
			transform->SetPosition(position);
			transform->SetScale(1.0f, 1.0f, 1.0f);
			transform->SetQuaternion(playerTrans->GetQuaternion());

			// 頂点データの設定
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
			// ここまで

			// 見た目の設定
			m_draw = AddComponent<PCTStaticDraw>();
			m_draw->SetOriginalMeshUse(true);
			m_draw->CreateOriginalMesh(m_vertices, m_indices);
			m_draw->SetTextureResource(m_TexKey);

			// 透明処理を有効に
			SetAlphaActive(true);

			// テクスチャ名がHPBAR_GREENなら
			if (m_TexKey == L"HPBAR_GREEN")
			{
				// 描画レイヤーを底面に
				SetDrawLayer((int)DrawLayer::Bottom);
			}
			else if (m_TexKey == L"HPBAR_RED") // HPBAR_REDなら
			{
				// 描画レイヤーを最底面に
				SetDrawLayer((int)DrawLayer::MostBottom);
			}
		}

	}

	void PlayerHpGauge::OnUpdate() {

		if (!m_playerStatus.expired()) {

			// 各種情報の取得
			auto transform = GetComponent<Transform>();
			auto playerStatusPtr = m_playerStatus.lock();
			auto cameraPtr = GetStage()->GetView()->GetTargetCamera();
			auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
			auto position = playerTrans->GetPosition();
			// ここまで

			// y方向にずらす
			position.y += m_AddPosY;
			transform->SetPosition(position);

			//向きをビルボード(画面に対して平行)にする
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
		// 1単位の大きさを計算
		float gaugeSizeDiff = m_DefaultSize.x / gaugeSizeLimit;
		for (int i = 0; i < 4; i++)
		{
			float currentLostGauge = gaugeSizeLimit - currentGaugeSize;
			if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
			{
				m_vertices[i].position.x = m_DefaultSize.x * 0.5f - (gaugeSizeDiff * currentLostGauge);
			}
		}
		// 頂点データの更新
		m_draw->UpdateVertices(m_vertices);
	}


}