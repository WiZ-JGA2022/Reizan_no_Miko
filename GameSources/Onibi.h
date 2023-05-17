/*!
@file Oni.h
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Onibi : public Enemy {

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_directionPoint;
		Vec3 m_directionPlayer;


		// ダメージを与える間隔
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 0.1f}
		};

	public:
		Onibi(const shared_ptr<Stage>& stage);
		~Onibi();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* 敵の移動処理
		*/
		void MoveEnemyPlayer();

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
		float GetEnemyStatus(const wstring& statusKey);

	};
}