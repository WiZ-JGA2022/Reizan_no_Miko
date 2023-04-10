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

		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		// 経験値取得量が必要経験値を超えたとき
		if (m_statusValue[L"EXP"] >= m_maxExp)
		{
			// 経験値レベルを上げる
			m_statusLevel[L"EXP"]++;
			// レベルアップイベントの実行
			levelUpEvent->LevelUpEvent();
			// EXPを0に戻す
			m_statusValue[L"EXP"] = 0;
			// 次回レベルアップまでに必要なEXP量を増やす
			m_maxExp = m_BaseRisingValue * m_statusLevel[L"EXP"];
		}

		// レベルアップイベントがアクティブなら
		if (levelUpEvent->GetEventActive())
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice(); 
			auto& pad = device.GetControlerVec()[0]; 

			// 十字キーの上、右、下で選ぶ
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(0));
				levelUpEvent->SetEventActive(false);
			}
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(1));
				levelUpEvent->SetEventActive(false);
			}
			if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				StatusLevelUpdate(levelUpEvent->GetSpriteNums(2));
				levelUpEvent->SetEventActive(false);
			}
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
