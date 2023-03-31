/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void PlayerStatusController::OnCreate()
	{
		for (int i = 0; i < statusName.size(); i++)
		{
			status.emplace_back(0);
			status[i] = statusValue[statusName[i]] + (statusLevel[statusName[i]] * MAGNIFICATION);

		}
		maxHp = statusValue[statusName[0]] + (statusLevel[statusName[0]] * MAGNIFICATION);
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
		m_maxExp = 10 * (m_expLevel - 1) + m_previousExp;

		// //HPが0になったら
		//if (status[0] < 0)
		//{
		//	GetStage()->RemoveGameObject<PlayerShot>(GetThis<PlayerShot>());
		//	GetStage()->RemoveGameObject<PlayerController>(GetThis<PlayerController>());

		//}
	}
	void PlayerStatusController::StatusLevelUpdate(int selectStatusNum)
	{
		// レベルを上げる
		statusLevel[statusName[selectStatusNum]]++;
		//ステータス上昇値を反映する
		status[selectStatusNum] += MAGNIFICATION;
		//auto player = GetComponent<PlayerController>()->PlayerSpeedUp(status[3]);
		//GetComponent<PlayerShot>(LevelUpShotDelay(status[4]));
		//if (selectStatusNum == 0)
		//{
		//	//maxHp += MAGNIFICATION;
		//}
		// 経験値を0に戻す
		//expItem.ResetExpCount();
		//// レベルアップイベントの終了
		//levelUpPanel.GetComponent<LevelUpEvent>().PanelUnActivated();

	} // end StatusLevelUpdate

	// 敵から受けるダメージの処理
	void PlayerTakenDamage()
	{
		// マジックナンバーの部分を後々敵の攻撃力に変更する
		float enemyATK = 1.0f;

		// 敵の攻撃力分自分の体力を減らす
		//status[0] -= enemyATK;
	} // end PlayerTakenDamage

}
