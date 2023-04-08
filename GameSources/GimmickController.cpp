/*!
@file GimmickController.cpp
@brief ギミックを出すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GimmickController::GimmickController(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	GimmickController::~GimmickController() {}

	void GimmickController::OnCreate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto playerTrans = player->GetComponent<Transform>();

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(playerTrans->GetPosition());

		for (int i = 0; i < m_GimmickPosition->length(); i++)
		{
			GetStage()->AddGameObject<SpurtLava>(m_GimmickPosition[i], m_GimmickScale);
		}
	}

	void GimmickController::OnUpdate()
	{
	}
}