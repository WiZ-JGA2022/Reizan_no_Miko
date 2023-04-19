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
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// 衝突判定はNone
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpurtLava");
	}

	void SpurtLava::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
			
		// 基本的にコリジョンを待機状態にしておく
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		ptrColl->SetDrawActive(false);

		// プレイヤーの状態が実行状態のときRスティックを押し込んだら
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (player->GetCondition() == 1)
		{
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
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

			// ダメージを与える間隔毎にコリジョンをアクティブにする
			if (m_removeDelayFlame % m_DamageIntervalFlame == 0)
			{
				ptrColl->SetUpdateActive(true);
				ptrColl->SetDrawActive(true);
			}
			// 削除までの時間が0になったら
			if (m_removeDelayFlame <= 0)
			{
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
}