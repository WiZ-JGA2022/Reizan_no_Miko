/*!
@file PlayerStatusController.cpp
@brief プレイヤーのステータスを管理するクラスの実装
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"damage.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
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

	// 敵から受けるダメージの処理
	void PlayerStatusController::PlayerDamageProcess(float damage)
	{
		// 防御力の軽減を追加したダメージ量の計算
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));
		// ダメージ分自分の体力を減らす
		m_statusValue[L"HP"] -= totalDamage;

		// SEの再生
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"PLAYERDAMAGE_SE", 0, 0.3f);

		//エフェクトのプレイ
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, player->GetComponent<Transform>()->GetPosition(), Vec3(1.0f));
	} // end PlayerTakenDamage
}
