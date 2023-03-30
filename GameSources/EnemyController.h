/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class EnemyController : public GameObject {

		const int m_RandomRange; // 乱数の最大範囲
		const int m_Distance; // この変数に設定した数値分Playerと離れる
		const int m_DelayCount; 

		int m_delayFlame;

		Vec3 m_position; // このオブジェクトの位置情報
		Vec3 m_enemyPos; // 敵の位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		EnemyController(const shared_ptr<Stage>& stage);
		~EnemyController();

		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross
