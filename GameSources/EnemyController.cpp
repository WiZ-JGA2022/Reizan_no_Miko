/*!
@file EnemyController.cpp
@brief “G‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void EnemyController::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetOwnShadowActive(true);

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(2.0f, 0.0f, 2.0f);

	}

	void EnemyController::OnUpdate()
	{	
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto enemyPos = m_transform->GetPosition();
		auto playerPos = m_playerObj->GetPosition();


		if (playerPos.x == enemyPos.x) { m_forceX = 0; }
		if (playerPos.x < enemyPos.x) { m_forceX = -1; }
		if (playerPos.x > enemyPos.x) { m_forceX = +1; }

		if (playerPos.z == enemyPos.z) { m_forceZ = 0; }
		if (playerPos.z < enemyPos.z) { m_forceZ = -1; }
		if (playerPos.z > enemyPos.z) { m_forceZ = +1; }


		float rotationY = atan2f(playerPos.z, playerPos.x);
		float enemyMoveX = enemyPos.x + m_forceX * delta;
		float enemyMoveZ = enemyPos.z + m_forceZ * delta;
		m_transform->SetRotation(Vec3(0, rotationY + XM_PIDIV2, 0));
		m_transform->SetPosition(enemyMoveX, enemyPos.y, enemyMoveZ);

	}

}
//end basecross
