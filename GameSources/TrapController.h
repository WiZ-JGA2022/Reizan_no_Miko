/*!
@file TrapController.h
@brief 罠を管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapController : public GameObject {
		
		enum class TrapState
		{
			Wait,		// 待機
			Active,		// 実行
			ActiveDelay	// 実行遅延
		};
		enum TrapState m_isState = TrapState::Wait;

		const int m_TrapActiveDelaySeconds = 180;
		const int m_TrapDamageDelayFlame = 180;

		int m_trapDamageDelay;

		shared_ptr<Transform> m_transform;

	public :
		TrapController(const shared_ptr<Stage>& stage);
		~TrapController();

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSpurtLava();
		int GetDamageFlame();
		int GetDamageDelay();

	};
}
