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

		// ステータス名
		std::map<int, wstring> m_statusName = {
			{0, L"HP"},
			{1, L"ATK"},
			{2, L"DEF"},
			{3, L"SPD"},
		};

		// ステータス値
		std::map<wstring, float> m_statusValue = {
			{L"HP", 10.0f},
			{L"ATK", 1.0f},
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

		void MoveEnemy();

		void EnemyDamageProcess();
		float GetEnemyStatus(wstring statusKey);
	};
}