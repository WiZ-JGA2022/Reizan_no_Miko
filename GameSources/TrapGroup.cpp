/*!
@file TrapGroup.cpp
@brief 罠の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_activeFlame(m_DamageActiveDelayFlame),
		m_removeDelayFlame(m_RemoveDelayCount),
		m_scale(scale),
		m_position(position)
	{
	}
	SpurtLava::~SpurtLava() {}

	void SpurtLava::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(Vec3(1.0f, 1.0f, 1.0f));
		m_transform->SetRotation(Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f));
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"SPURTLAVA_MODEL");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		// 見た目の設定
		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"SPURTLAVA_MODEL");
		drawComp->SetMeshToTransformMatrix(spanMat);

		// タグの追加
		AddTag(L"SpurtLava");
		// 透明処理を有効化
		SetAlphaActive(true);
		// 描画レイヤーを設定
		SetDrawLayer((int)DrawLayer::Bottom);

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"Lava.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
	}

	void SpurtLava::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
			
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		// 基本的にコリジョンを待機状態にしておく
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);

		// プレイヤーが描画されなくなったら
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (!player->GetDrawActive())
		{
			// エフェクトとSEを停止する
			if (m_isState == TrapState::Active)
			{
				m_EfkPlay->StopEffect();
			}
			XAPtr->Stop(m_se[0]);
			XAPtr->Stop(m_se[1]);
		}

		// プレイヤーの状態がスタンバイ状態でないとき
		if (player->GetCondition() != 0)
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& firstStage = dynamic_pointer_cast<FirstStage>(stage);
			// ステージが切り替わったら
			if (firstStage->GetChangingStage())
			{
				// エフェクトとSEを停止する
				if (m_isState == TrapState::Active)
				{
					m_EfkPlay->StopEffect();
				}
				XAPtr->Stop(m_se[0]);
				XAPtr->Stop(m_se[1]);
			}

			if (m_isState == TrapState::Wait)
			{
				// Rスティックを押し込んだら
				if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				{
					// SEの再生
					m_se[0] = XAPtr->Start(L"LAVA_SE", 0, 0.3f);
					// 実行待機状態に入る
					m_isState = TrapState::ActiveDelay;
				}
			}
		}

		// 実行待機状態なら
		if (m_isState == TrapState::ActiveDelay)
		{
			// 待機時間を減少
			m_activeFlame--;
			// 待機時間が終わったら
			if (m_activeFlame <= 0)
			{
				// コリジョンを取得した大きさに変更
				ptrColl->SetMakedSize(3);
				// SEの再生
				m_se[1] = XAPtr->Start(L"SPURTLAVA_SE", 0, 0.3f);
				// 実行状態に入る
				m_isState = TrapState::Active;
				// 待機時間を初期化しておく
				m_activeFlame = m_DamageActiveDelayFlame;

				//エフェクトのプレイ
				m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, m_transform->GetPosition(), Vec3(0.5f));
			}
		}

		// 実行状態なら
		if (m_isState == TrapState::Active)
		{
			// 削除までの時間を経過させる
			m_removeDelayFlame--;

			// ダメージを与える間隔毎にコリジョンをアクティブにする
			if (m_removeDelayFlame % m_DamageIntervalFlame == 0)
			{
				ptrColl->SetUpdateActive(true);
			}
			// 削除までの時間が0になったら
			if (m_removeDelayFlame <= 0)
			{
				XAPtr->Stop(m_se[0]);
				XAPtr->Stop(m_se[1]);
				// 待機状態に移行
				m_isState = TrapState::Wait;
				// このオブジェクトの削除
				GetStage()->RemoveGameObject<SpurtLava>(GetThis<SpurtLava>());
			}
		}
	}


	SpikeTrap::SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_scale(scale),
		m_position(position)
	{
	}
	SpikeTrap::~SpikeTrap() {}

	void SpikeTrap::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpikeTrap");

		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::Bottom);

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"E_aura.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//エフェクトのプレイ
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, m_transform->GetPosition(), Vec3(1.0f));
	}

	void SpikeTrap::OnUpdate()
	{
		// 各種オブジェクトの情報を取得
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");

		// プレイヤーがスタンバイ状態じゃないとき
		if (player->GetCondition() != 0)
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& firstStage = dynamic_pointer_cast<FirstStage>(stage);
			// ステージが変わったら
			if (firstStage->GetChangingStage())
			{
				// エフェクトを消す
				m_EfkPlay->StopEffect();
			}
		}
		else
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& standbyStage = dynamic_pointer_cast<StandbyStage>(stage);
			if (standbyStage->GetChangingStage())
			{
				// エフェクトを消す
				m_EfkPlay->StopEffect();
			}
		}

		// 「プレイヤーが消える」「時間切れになる」「石が壊れる」のうちどれかを満たしたら
		if (!player->GetDrawActive() || time->GetTimeLeft() < 0.0f || stone->GetCurrentHp() < 0.0f)
		{
			// エフェクトを消す
			m_EfkPlay->StopEffect();
		}
	}

	void SpikeTrap::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// enemyに当たったら
		if (other->FindTag(L"Enemy"))
		{
			// 棘オブジェクトを追加し、このオブジェクトを消去
			GetStage()->AddGameObject<SpikeModel>(m_transform->GetPosition());
			GetStage()->RemoveGameObject<SpikeTrap>(GetThis<SpikeTrap>());
		}
	}
}