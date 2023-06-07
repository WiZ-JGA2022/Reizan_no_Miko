/*!
@file Oni.h
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Onibi : public Enemy {
		//エフェクト
		shared_ptr<EfkEffect> m_damageEffect;
		shared_ptr<EfkEffect> m_diedEffect;

		shared_ptr<EfkPlay> m_EfkPlay; //エフェクト実行オブジェクト

		Vec3 m_position; // 位置
		Vec3 m_scale; // 大きさ
		Vec3 m_direction; // 方向

		const int m_DamageDelayCount; // ダメージを与える間隔
		const float m_RecastCount; // 弾発射間隔

		int m_damageDelayFlame;
		float m_recastFlame;

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 1.0f}
		};

	public:
		Onibi(const shared_ptr<Stage>& stage, const Vec3& position);
		~Onibi();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* 主人公に向かって移動する処理
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