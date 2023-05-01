/*!
@file SimpleEnemy.h
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class SimpleEnemy : public Enemy {

		Vec3 m_position;

		Vec3 m_randomDirection;
		Vec3 m_randomPosition;

		Vec3 m_direction[3] = {
			Vec3(0.0f, 0.0f, -40.0f),
			Vec3(-20.0f, 0.0f, 0.0f),
			Vec3(20.0f, 0.0f, -30.0f)
		};

		Vec3 m_points[4] = {
			Vec3(20.0f, 1.5f, 40.0f),
			Vec3(20.0f, 1.5f, 20.0f),
			Vec3(-20.0f, 1.5f, 20.0f),
			Vec3(0.0f, 1.5f, 0.0f)
		};
		
		int m_currentPointIndex;

		// ダメージを与える間隔
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		Vec3 m_directionPlayer;
		Vec3 m_directionKeyStone;
		Vec3 m_directionBlockingStone;

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		SimpleEnemy(const shared_ptr<Stage>& stage, const Vec3& position);
		~SimpleEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* 敵の移動処理
		*/
		void MoveEnemy() override;
		void MoveEnemyPlayer();//player
		void MoveEnemyKeyStone();//keystone
		void MoveEnemyBlockingStone();//blockingStone

		/**
		* 敵が受けるダメージの計算
		*/
		void EnemyDamageProcess(float damage);

		/**
		* 任意の敵のステータスを取得する関数
		*
		* @param statusKey 取得したいステータスの名前
		*
		* @return 指定したステータスの値
		*/
		float GetEnemyStatus(wstring statusKey);

	};
}