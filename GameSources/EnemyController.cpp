/*!
@file EnemyController.cpp
@brief 敵など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyController::EnemyController(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_RandomRange(20),
		m_position(Vec3(0.0f, 0.0f, 5.0f))
	{
	}
	EnemyController::~EnemyController() {}

	void EnemyController::OnCreate()
	{
		srand((unsigned int)time(NULL));

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);

		GetStage()->AddGameObject<Enemy>(m_position);

	}

	void EnemyController::OnUpdate()
	{	
		// このオブジェクトの位置を基準としたランダムな場所に出現させる
		m_targetPos = Vec3(m_position.x + rand() % m_RandomRange, m_position.y + rand() % m_RandomRange, m_position.z);
		auto group = GetStage()->GetSharedObjectGroup(L"EnemyGroup"); // Targetグループの取得
		auto& vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				if (!shObj->IsUpdateActive()) {
					auto target = dynamic_pointer_cast<Enemy>(shObj);
					if (target) {
						target->SetPosition(m_targetPos);
						return;
					}
				}
			}
		}
	}

}
//end basecross
