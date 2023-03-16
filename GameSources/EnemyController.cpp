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

		auto m_transform = GetComponent<Transform>();
		m_transform->SetPosition(Vec3(1.0f));

		m_playerTrans = m_playerObj->GetComponent<Transform>();
		m_playerPos = m_playerTrans->GetPosition();
		m_transform->SetPosition(1.0f, 0.0f, 1.0f);
		m_transform->SetRotation(Vec3(0.0f));
	}

	void EnemyController::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime(); 

		//auto pos = m_transform->GetPosition();
		//pos += 1.0f * delta;

		//m_transform->SetPosition(1.0f, 0.0f, 1.0f);
		//m_transform->SetPosition(pos);

		float rotY = atan2f(-m_playerPos.z, m_playerPos.x); 
		m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0));
	}
}
//end basecross
