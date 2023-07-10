/*!
@file PlayerController.h
@brief プレイヤーキャラ
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class PlayerController : public GameObject
	{
		// プレイヤーの状態
		enum class PlayerCondition {
			Standby, // 準備状態
			Play // 防衛状態
		};

		// プレイヤーの行動
		enum class PlayerMotion {
			Wait, // 待機モーション
			Walk, // 歩きモーション
			Died  // 死亡モーション
		};

		// 置ける罠の数
		enum class TrapLimit {
			SpikeTrap = 5, // 棘罠
			SpurtLava = 1 // 溶岩罠
		};

		PlayerCondition m_condition = PlayerCondition::Standby; // 状態

		PlayerMotion m_action = PlayerMotion::Wait; // 行動

		// 罠の上限数
		TrapLimit m_trapLimit[2] = {
			TrapLimit::SpikeTrap,
			TrapLimit::SpurtLava
		};

		// プレイヤーの操作に使用するボタン
		const WORD BUTTON_SHOT = XINPUT_GAMEPAD_X;
		
		const float m_RecastCount; // 弾発射間隔

		int m_trapCount[2] = { 0 }; // 罠の数

		float m_recastFlame; // 発射間隔

		Vec3 m_position; // 位置
		Quat m_quaternion; // 回転

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント
	public:
		// コンストラクタ
		PlayerController(const shared_ptr<Stage>& stage, const int condition);
		PlayerController(const shared_ptr<Stage>& stage, const Vec3& position, const Quat& quaternion, const int condition);
		// デストラクタ
		~PlayerController();

		void OnCreate() override; // 初期化
		void OnUpdate() override; // 更新処理
		
		/**
		* プレイヤーの移動処理
		*/
		void PlayerMoveProcess();

		/**
		* プレイヤーの状態を取得
		* 
		* @return m_condition 状態
		*/ 
		int GetCondition()
		{
			return (int)m_condition;
		}
		
		// 罠の設置上限を取得
		int GetTrapLimit(int index)
		{
			return (int)m_trapLimit[index];
		}

		// 設置されている罠の数
		int GetTrapCount(int index)
		{
			return m_trapCount[index];
		}
	};
}
