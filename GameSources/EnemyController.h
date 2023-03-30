/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class EnemyController : public GameObject {

		const int m_RandomRange; // 乱数の範囲

		Vec3 m_position; // このオブジェクトの位置情報
		Vec3 m_targetPos; // 的の位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		EnemyController(const shared_ptr<Stage>& stage);
		~EnemyController();

		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross
