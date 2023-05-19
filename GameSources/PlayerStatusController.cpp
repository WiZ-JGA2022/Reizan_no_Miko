/*!
@file PlayerStatusController.cpp
@brief プレイヤーのステータスを管理するクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_BaseRisingValue(10),
		m_DamageDelayCount(60),
		m_maxHp(50),
		m_maxExp(5),
		m_beforeMaxExp(m_maxExp),
		m_damageDelayFlame(m_DamageDelayCount)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		// ステータス上昇値の初期化
		for (int i = 0; i < m_statusName.size(); i++)
		{
			m_statusRisingValue.emplace_back(0);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// プレイヤーが居なかったら
		if (!player->GetDrawActive())
		{
			// 処理を停止する
			return;
		}
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
			m_maxHp += m_BaseRisingValue;
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
	} // end StatusLevelUpdate

	// 敵から受けるダメージの処理
	void PlayerStatusController::PlayerDamageProcess(float damage)
	{
		// 防御力の軽減を追加したダメージ量の計算
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));
		// ダメージ分自分の体力を減らす
		m_statusValue[L"HP"] -= totalDamage;
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"PLAYERDAMAGE_SE", 0, 0.1f);
	} // end PlayerTakenDamage

	float PlayerStatusController::GetStatusValue(wstring statusKey)
	{
		return m_statusValue[statusKey];
	}

	int PlayerStatusController::GetMaxHp()
	{
		return m_maxHp;
	}

	int PlayerStatusController::GetMaxExp()
	{
		return m_maxExp;
	}

	void PlayerStatusController::ExpValueUpdate(int expValue)
	{
		m_statusValue[L"EXP"] += expValue;
	}
}
