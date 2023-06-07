/*!
@file Oni.h
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Oni : public Enemy {
		// エフェクト
		shared_ptr<EfkEffect> m_diedEffect;
		shared_ptr<EfkEffect> m_damageEffect;
		
		shared_ptr<EfkPlay> m_EfkPlay; // エフェクト実行オブジェクト

		wstring m_diedEffectStr;
		wstring m_damageEffectStr;

		Vec3 m_position; // 位置
		Vec3 m_scale; // 大きさ
		Vec3 m_direction; // 方向
		
		int m_currentPointIndex; // 現在の通過点

		// ダメージを与える間隔
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		bool m_died; // 死亡したかどうかのフラグ

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		// コンストラクタ
		Oni(const shared_ptr<Stage>& stage, const Vec3& position);
		// デストラクタ
		~Oni();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;

		// 衝突応答処理(当たった瞬間)
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		// 衝突応答処理(当たってる間)
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* 敵の移動処理
		* 
		* @param point 位置
		*/
		void MoveEnemyPoint(const Vec3& point);

		/**
		* 敵が受けるダメージの計算
		* 
		* @param damage ダメージ量
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