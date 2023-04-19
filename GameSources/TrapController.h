/*!
@file TrapController.h
@brief 㩂��Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TrapController : public GameObject {
		
		enum class TrapState
		{
			Wait,		// �ҋ@
			Active,		// ���s
			ActiveDelay	// ���s�x��
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
