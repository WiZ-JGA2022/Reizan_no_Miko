/*!
@file Item.cpp
@brief アイテムの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Item::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_itemScale);
		m_transform->SetPosition(m_itemPosition);

		auto ItemColl = AddComponent<CollisionObb>();
		ItemColl->SetAfterCollision(AfterCollision::None);

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		// デルタタイムの取得
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		// 各種ベクトルの取得
		auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得

		m_direction = playerPos - pos; // プレイヤーへの方向を計算

		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +
			m_direction.y * m_direction.y +
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// ここまで

		pos += m_direction * m_speed * delta;	// 移動の計算
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理

		////一定の範囲にプレイヤーが入ったらその方向に移動する
		//auto ItemAreapos = m_inArea;
		//bool IteminArea(false)
		//	if (Playerpos.x > ItemAreapos)
		//	{

		//	}
	}

	void Item::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player"))
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
	}

}
//end basecross
