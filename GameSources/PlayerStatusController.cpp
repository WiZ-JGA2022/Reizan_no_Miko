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
			m_statusRisingValue.emplace_back(0);
		}
	}

	void PlayerStatusController::OnUpdate()
	{
		//if (player == null)
		//{
		//	return;
		//}
		//expCount = expItem.GetExpCount(); // 現在経験値を取得

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

		// //HPが0になったら
		//if (m_statusRisingValue[0] < 0)
		//{
		//	GetStage()->RemoveGameObject<PlayerShot>(GetThis<PlayerShot>());
		//	GetStage()->RemoveGameObject<PlayerController>(GetThis<PlayerController>());

		//}
	}
	void PlayerStatusController::StatusLevelUpdate(int selectStatusNum)
	{
		// レベルを上げる
		m_statusLevel[m_statusName[selectStatusNum]]++;
		//ステータス上昇値を反映する
		switch (selectStatusNum)
		{
		case 0 : // HP
			m_statusRisingValue[selectStatusNum] += m_BaseRisingValue;			// 上昇値は10(固定値)
			m_statusValue[m_statusName[selectStatusNum]] += m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 1 : // ATK
		case 3 : // SPD
			m_statusRisingValue[selectStatusNum] += m_BaseRisingValue / 100.0f + 1;	// 上昇値は0.1(10%)
			m_statusValue[m_statusName[selectStatusNum]] *= m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 2 : // DEF
		case 4 : // HASTE
			m_statusRisingValue[selectStatusNum] += m_BaseRisingValue / 1000.0f + 1;	// 上昇値は0.01(1%)
			m_statusValue[m_statusName[selectStatusNum]] *= m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		case 5 : // PICKUP
			m_statusRisingValue[selectStatusNum] += m_BaseRisingValue / 200.0f + 1;	// 上昇値は0.05(5%)
			m_statusValue[m_statusName[selectStatusNum]] *= m_statusRisingValue[selectStatusNum]; // 上昇量の反映
			break;
		default :
			break;
		}
		//auto player = GetComponent<PlayerController>()->PlayerSpeedUp(m_statusRisingValue[3]);
		//GetComponent<PlayerShot>(LevelUpShotDelay(m_statusRisingValue[4]));
		//if (selectStatusNum == 0)
		//{
		//	//maxHp += m_BaseRisingValue;
		//}
		// 経験値を0に戻す
		//expItem.ResetExpCount();
		//// レベルアップイベントの終了
		//levelUpPanel.GetComponent<LevelUpEvent>().PanelUnActivated();

	} // end StatusLevelUpdate

	float PlayerStatusController::GetStatusValue(wstring m_statusName)
	{
		return m_statusValue[m_statusName];
	}

	// 敵から受けるダメージの処理
	void PlayerStatusController::PlayerDamageProcess()
	{
		// マジックナンバーの部分を後々敵の攻撃力に変更する
		float enemyATK = 1.0f;
		// 防御力の軽減を追加したダメージ量の計算
		float damage = enemyATK + (1 - m_statusValue[L"DEF"]);

		// ダメージ分自分の体力を減らす
		m_statusValue[L"HP"] -= damage;
	} // end PlayerTakenDamage

}
