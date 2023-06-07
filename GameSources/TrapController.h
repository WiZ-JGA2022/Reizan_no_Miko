/*!
@file TrapController.h
@brief 罠を管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapController : public GameObject {
		
		// 罠の状態
		enum class TrapState
		{
			Wait,		// 待機
			Active,		// 実行
			ActiveDelay	// 実行遅延
		};
		enum TrapState m_isState = TrapState::Wait;

		const int m_TrapActiveDelaySeconds = 180; // トラップが実行状態になるまでの遅延
		const int m_TrapDamageDelayFlame = 180; // トラップがダメージを与える間隔

		int m_trapDamageDelay; 

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public :
		// コンストラクタ
		TrapController(const shared_ptr<Stage>& stage);
		// デストラクタ
		~TrapController();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;

		// 溶岩罠の作成
		void CreateSpurtLava();

	};
}
