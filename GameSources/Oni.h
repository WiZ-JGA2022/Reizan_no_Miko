/*!
@file Oni.h
@brief 単純な動きの敵
*/

#pragma once
#include "stdafx.h"
#include "Enemy.h"

namespace basecross {
	class Oni : public Enemy {
		//エフェクト
		shared_ptr<EfkEffect> m_diedEffect;
		shared_ptr<EfkEffect> m_damageEffect;
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_EfkPlay;

		wstring m_diedEffectStr;
		wstring m_damageEffectStr;

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_direction;
		
		int m_currentPointIndex;

		// ダメージを与える間隔
		const int m_DamageDelayCount;
		int m_damageDelayFlame;

		float m_alpha;
		bool m_died;

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 3.0f}
		};

	public :
		Oni(const shared_ptr<Stage>& stage, const Vec3& position);
		~Oni();

		void OnCreate() override;
		void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;

		/**
		* 敵の移動処理
		*/
		void MoveEnemyPoint(const Vec3& point);//point

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