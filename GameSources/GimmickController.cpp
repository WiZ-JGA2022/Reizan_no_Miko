/*!
@file GimmickController.cpp
@brief ギミックを出すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GimmickController::GimmickController(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_gimmickDamageDelay(m_GimmickDamageDelayFlame)
	{
	}
	GimmickController::~GimmickController() {}

	void GimmickController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(Vec3(0));
	}

	void GimmickController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = player->GetComponent<Transform>();
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");

		if ((int)time->GetTimeLeft() == m_GimmickCreateDelaySeconds)
		{
			m_isState = GimmickState::DamageDelay;
			for (int i = 0; i < 10; i++)
			{
				m_gimmickPosition[i] = playerTrans->GetPosition() + m_GimmickPosition[i];
			}
		}
		if (m_isState == GimmickState::DamageDelay)
		{
			m_gimmickDamageDelay--;
			if (m_gimmickDamageDelay <= 0)
			{
				m_isState = GimmickState::Active;
				m_gimmickDamageDelay = m_GimmickDamageDelayFlame;
			}
		}
		if (m_isState == GimmickState::Active)
		{
			CreateSpurtLava();
			m_isState = GimmickState::UnActive;
		}
	}

	void GimmickController::CreateSpurtLava()
	{
		for (int i = 0; i < 10; i++)
		{
			GetStage()->AddGameObject<SpurtLava>(m_gimmickPosition[i], m_GimmickScale);
		}
	}

	int GimmickController::GetDamageFlame()
	{
		return m_GimmickDamageDelayFlame;
	}
	int GimmickController::GetDamageDelay()
	{
		return m_gimmickDamageDelay;
	}
}