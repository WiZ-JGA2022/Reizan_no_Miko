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

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(2.0f, 1.0f, 2.0f);


	}

	void EnemyController::OnUpdate()
	{	
		//auto playerObj = GetComponent<Player>;
		//auto playerTrans = playerObj->GetComponent<Transform>();

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto enemyPos = transComp->GetPosition();
		auto playerTrans = m_playerObj->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();


		if (playerPos.x == enemyPos.x) { m_forceX = 0; }
		if (playerPos.x < enemyPos.x) { m_forceX = -1; }
		if (playerPos.x > enemyPos.x) { m_forceX = +1; }

		if (playerPos.z == enemyPos.z) { m_forceZ = 0; }
		if (playerPos.z < enemyPos.z) { m_forceZ = -1; }
		if (playerPos.z > enemyPos.z) { m_forceZ = +1; }


		float rotationY = atan2f(playerPos.z, playerPos.x);
		float enemyMoveX = enemyPos.x + m_forceX * delta;
		float enemyMoveZ = enemyPos.z + m_forceZ * delta;
		transComp->SetRotation(Vec3(0, rotationY + XM_PIDIV2, 0));
		transComp->SetPosition(enemyMoveX, enemyPos.y, enemyMoveZ);

	}

}
//end basecross
