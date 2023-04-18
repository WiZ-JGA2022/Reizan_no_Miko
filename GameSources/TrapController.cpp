/*!
@file TrapController.cpp
@brief „©Çä«óùÇ∑ÇÈÉNÉâÉXÇÃé¿ëï
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TrapController::TrapController(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_trapDamageDelay(m_TrapDamageDelayFlame)
	{
	}
	TrapController::~TrapController() {}

	void TrapController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(Vec3(0));
	}

	void TrapController::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			m_isState = TrapState::ActiveDelay;
		}
		if (m_isState == TrapState::ActiveDelay)
		{
			m_trapDamageDelay--;
			if (m_trapDamageDelay <= 0)
			{
				m_isState = TrapState::Active;
				m_trapDamageDelay = m_TrapDamageDelayFlame;
			}
		}
		if (m_isState == TrapState::Active)
		{
			CreateSpurtLava();
			m_isState = TrapState::Wait;
			GetStage()->RemoveGameObject<TrapController>(GetThis<TrapController>());
		}
	}

	void TrapController::CreateSpurtLava()
	{
		GetStage()->AddGameObject<SpurtLava>(m_transform->GetPosition(), Vec3(20.0f, 4.0f, 1.0f));
	}

	int TrapController::GetDamageFlame()
	{
		return m_TrapDamageDelayFlame;
	}
	int TrapController::GetDamageDelay()
	{
		return m_trapDamageDelay;
	}
}