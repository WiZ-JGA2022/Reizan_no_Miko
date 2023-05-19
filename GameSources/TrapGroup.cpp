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
		m_transform->SetScale(Vec3(5.0f, 5.0f, 1.0f));
		m_transform->SetRotation(Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f));
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetTextureResource(L"SPURT_LAVA");

		AddTag(L"SpurtLava");
		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::Bottom);
	}

	void SpurtLava::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
			
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		// 基本的にコリジョンを待機状態にしておく
		auto ptrColl = GetComponent<CollisionObb>();
		auto ptrDraw = GetComponent<PNTStaticDraw>();
		ptrColl->SetUpdateActive(false);
		ptrColl->SetDrawActive(false);

		// プレイヤーが実行状態かつトラップが待機状態のとき
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (player->GetCondition() == 1 && m_isState == TrapState::Wait)
		{
			//Rスティックを押し込んだら
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				// SEの再生
				m_se[0] = XAPtr->Start(L"LAVA_SE", 0, 0.3f);
				// 描画をやめる
				ptrDraw->SetDrawActive(false);
				// 実行待機状態に入る
				m_isState = TrapState::ActiveDelay;
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
				m_transform->SetScale(m_scale);
				m_transform->SetRotation(Vec3(0));
				// SEの再生
				m_se[1] = XAPtr->Start(L"SPURTLAVA_SE", 0, 0.3f);
				// 実行状態に入る
				m_isState = TrapState::Active;
				// 待機時間を初期化しておく
				m_activeFlame = m_DamageActiveDelayFlame;
			}
		}

		// 実行状態なら
		if (m_isState == TrapState::Active)
		{
			// 削除までの時間を経過させる
			m_removeDelayFlame--;
			GetStage()->GetSharedGameObject<EffectController>(L"EffectController")->PlayEffect(L"SpurtLava_Efc", m_transform->GetPosition(), 7.0f);

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

		//wstringstream wss;
		//wss << L"pos : " <<
		//	m_transform->GetPosition().x << L" " <<
		//	m_transform->GetPosition().y << L" " <<
		//	m_transform->GetPosition().z << endl;
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());
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

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SPIKE");

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpikeTrap");

		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::Bottom);
	}

	void SpikeTrap::OnUpdate()
	{
	}

	void SpikeTrap::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Enemy"))
		{
			GetStage()->RemoveGameObject<SpikeTrap>(GetThis<SpikeTrap>());
		}
	}


	//妨害するオブジェクト
	void BlockingStone::OnCreate()
	{
		auto collComp = AddComponent<CollisionSphere>();
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto playerPos = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>()->GetPosition();
		m_objectPosition = Vec3(playerPos.x, playerPos.y, playerPos.z + 5.0f);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_objectPosition);
		transComp->SetRotation(0.0f, 0.0f, 0.0f);
		transComp->SetScale(5.0f, 5.0f, 5.0f);

		AddTag(L"BlockingStone");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetTextureResource(L"STONE");//妨害用に変更必須

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void BlockingStone::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_objectPosition);

		m_delay--;
		if (m_delay <= 0)
		{
			auto drawComp = GetComponent<PNTStaticDraw>();
			drawComp->SetEmissive(Col4(0.6f, 0.6f, 0.6f, 1.0f)); // Normalカラー
		}
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (m_hp <= 0)
		{
			GetStage()->RemoveGameObject<BlockingStone>(GetThis<BlockingStone>());
		}
	}

	void BlockingStone::DamageProcess()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"STONEDAMAGE_SE", 0, 0.5f);
		auto drawComp = GetComponent<PNTStaticDraw>();
		drawComp->SetEmissive(Col4(1.0f, 0.2f, 0.2f, 1.0f));
		m_delay = m_DefaultDelay;
		m_hp -= 10.0f;
	}

}