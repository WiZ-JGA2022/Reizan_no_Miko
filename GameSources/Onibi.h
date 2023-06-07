/*!
@file Oni.h
@brief プレイヤーに直接くる敵
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
			{L"HP", 10.0f}, //HP
			{L"ATK", 10.0f}, //ATTACK
			{L"DEF", 1.0f}, //DRFENDER
			{L"SPD", 1.0f} //SPEED
		};

	public:
		//コンストラクタ
		Onibi(const shared_ptr<Stage>& stage, const Vec3& position);
		//デストラクタ
		~Onibi();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

		//当たった瞬間
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		//当たってる間
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