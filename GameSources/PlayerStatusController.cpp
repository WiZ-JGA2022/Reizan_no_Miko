/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void PlayerStatusController::OnStart()
	{

		for (int i = 0;i < i; i++)
		{

		}
	}

	void PlayerStatusController::OnUpdate()
	{
		//if (player == null)
		//{
		//	return;
		//}
		//expCount = expItem.GetExpCount();
		if (m_expCount >= m_maxExp)
		{
			m_previousExp = m_maxExp;

			m_expLevel++;
			//levelUpPanel.GetComponent<LevelUpEvent>().PanelActivated();
			m_expCount -= m_maxExp;
		}
		// 次回レベルアップまでに必要なEXP量を増やす
		m_maxExp = 10 * (m_expLevel - 1) + m_previousExp;

		// HPが0になったら
		//if (status[0] < 0)
		//{
		// 
		//}
	}
	void PlayerStatusController::StatusLevelUpdate()
	{
		// レベルを上げる
		//statusLevel[rndSelect]++;
		//ステータス上昇値を反映する
		//status[rndSelect] += MAGNIFICATION;
		//player.GetComponent<PlayerController>().PlayerSpeedUp(status[3]);
		//GetComponent<PlayerShot>(LevelUpShotDelay(status[4]));
		//if (rndSelect == 0)
		//{
		//	//smaxHp += MAGNIFICATION;
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
