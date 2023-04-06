/*!
@file Enemy.h
@brief 敵全体の親クラス
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Enemy : public GameObject {
		
		Vec3 m_position; // 初期位置
		Vec3 m_direction; // プレイヤーへの方向

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 10.0f},
			{L"DEF", 1.0f},
			{L"SPD", 1.0f},
		};

	public:
		Enemy(const shared_ptr<Stage>& stage);

		Enemy(const shared_ptr<Stage>& stage, 
			const Vec3& position
		);
		~Enemy();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// 衝突応答処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		/**
		* 敵の移動処理
		*/
		void MoveEnemy();

		/**
		* 敵が受けるダメージの計算
		*/
		void EnemyDamageProcess();

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