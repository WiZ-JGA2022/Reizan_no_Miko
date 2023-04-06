/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_BaseRisingValue(10),
		m_DelayCount(60),
		m_expLevel(1),
		m_expCount(0.0f),
		m_maxExp(10.0f),
		m_previousExp(10.0f),
		m_enemyATK(0),
		m_delayFlame(m_DelayCount)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(0);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (!player->GetDrawActive())
		{
			return;
		}

		m_delayFlame--;

		// 経験値取得量と必要経験値が同じ場合(レベルアップ処理)
		if (m_expCount >= m_maxExp)
		{
			m_previousExp = m_maxExp;

			m_expLevel++;
			auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
			levelUpEvent->LevelUpEvent();
			m_expCount -= m_maxExp;
		}
		// 次回レベルアップまでに必要なEXP量を増やす
		m_maxExp = m_BaseRisingValue * (m_expLevel - 1) + m_previousExp;

		//wstringstream wss;
		//wss << L"HP : " <<
		//	m_statusValue[L"HP"] << "\n"
		//	<< L"ATK : " <<
		//	m_statusValue[L"ATK"] << "\n"
		//	<< L"DEF : " <<
		//	m_statusValue[L"DEF"] << "\n"
		//	<< L"SPD : " <<
		//	m_statusValue[L"SPD"] << "\n"
		//	<< L"HASTE : " <<
		//	m_statusValue[L"HASTE"] << "\n"
		//	<< L"PICKUP : " <<
		//	m_statusValue[L"PICKUP"] << endl;
		//auto& app = App::GetApp();
		//auto scene = app->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

	}
	void PlayerStatusController::StatusLevelUpdate(int selectStatusNum)
	{
		// レベルを上げる
		m_statusLevel[m_statusName[selectStatusNum]]++;
		//ステータス上昇値を反映する
		switch (selectStatusNum)
		{
		case 0 : // HP
			// 上昇値は10(固定値)
			m_statusValue[m_statusName[selectStatusNum]] += m_BaseRisingValue; // 上昇量の反映
			break;
		case 1 : // ATK
		case 3 : // SPD
			m_statusRisingValue[selectStatusNum] = 
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 100.0f);	// 上昇値は0.1(10%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 2 : // DEF
		case 4 : // HASTE
			m_statusRisingValue[selectStatusNum] = 
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 1000.0f);	// 上昇値は0.01(1%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 5 : // PICKUP
			m_statusRisingValue[selectStatusNum] = 
				m_DefaultStatusValue[selectStatusNum] * (m_BaseRisingValue / 200.0f);	// 上昇値は0.05(5%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		default :
			break;
		}
		// 経験値を0に戻す
		//expItem.ResetExpCount();

	} // end StatusLevelUpdate

	float PlayerStatusController::GetStatusValue(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}

	// 敵から受けるダメージの処理
	void PlayerStatusController::PlayerDamageProcess()
	{		
		// 防御力の軽減を追加したダメージ量の計算
		float damage = m_enemyATK - (m_enemyATK * (m_statusValue[L"DEF"] - 1.0f));
		if (m_delayFlame <= 0)
		{
			// ダメージ分自分の体力を減らす
			m_statusValue[L"HP"] -= damage;
			m_delayFlame = m_DelayCount;
		}
	} // end PlayerTakenDamage

	void PlayerStatusController::SetEnemyATK(float ATK)
	{
		m_enemyATK = ATK;
	}
}
