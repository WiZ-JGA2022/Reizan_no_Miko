/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(1);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
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
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 100.0f);	// 上昇値は0.1(10%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 2 : // DEF
		case 4 : // HASTE
			m_statusRisingValue[selectStatusNum] = 
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 1000.0f);	// 上昇値は0.01(1%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 5 : // PICKUP
			m_statusRisingValue[selectStatusNum] = 
				m_statusValue[m_statusName[selectStatusNum]] * (m_BaseRisingValue / 200.0f);	// 上昇値は0.05(5%)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		default :
			break;
		}
		// 経験値を0に戻す
		//expItem.ResetExpCount();

	} // end StatusLevelUpdate

	float PlayerStatusController::GetStatusValue(wstring m_statusName)
	{
		return m_statusValue[m_statusName];
	}

	// 敵から受けるダメージの処理
	void PlayerStatusController::PlayerDamageProcess()
	{
		auto enemy = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		auto& vec = enemy->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				if (shObj->IsUpdateActive()) {
					auto shEnemy = dynamic_pointer_cast<Enemy>(shObj);
					if (shEnemy) {
						m_enemyATK.emplace_back(shEnemy->GetEnemyStatus(L"ATK"));
					}
				}
			}
		}

		// 防御力の軽減を追加したダメージ量の計算
		float damage = m_enemyATK[0] - (m_enemyATK[0] * (m_statusValue[L"DEF"] - 1.0f));
		if (m_delayFlame <= 0)
		{
			// ダメージ分自分の体力を減らす
			m_statusValue[L"HP"] -= damage;
			m_delayFlame = m_DelayCount;
		}
	} // end PlayerTakenDamage

}
