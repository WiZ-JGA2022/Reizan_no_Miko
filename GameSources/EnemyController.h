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
		const int m_DelayCount; // 敵の生成遅延

		int m_delayFlame; // 遅延		
		int m_enemyNum; // 識別番号

		//敵の位置の符号
		int m_sign_x; 
		int m_sign_z;

		Vec3 m_position; // このオブジェクトの位置情報
		Vec3 m_enemyPos; // 敵の位置情報

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		EnemyController(const shared_ptr<Stage>& stage);
		~EnemyController();

		void OnCreate() override;
		void OnUpdate() override;

		/**
		* 敵の識別番号を取得する関数
		* 
		* @return 敵の識別番号
		*/
		int GetEnemyNumber();
	};

}
//end basecross
