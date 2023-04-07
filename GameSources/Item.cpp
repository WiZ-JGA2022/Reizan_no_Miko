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

		//Enemyが消えたら生成
		auto EnemyOut = m_enemydis;
		auto EnemyDieout = GetStage()->GetSharedGameObject<Enemy>(L"Enemy");
			 
		//if (EnemyOut && EnemyDieout < PlayerBullet)
		//{
		//	
		//	GetStage()->AddGameObject<Item>(GetThis<EnemyController>());
		//	return;
		//}

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto pos = m_transform->GetPosition();
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得

		m_direction = playerPos - pos; // プレイヤーへの方向を計算

		//playerが一定の範囲に入ったら動く（条件式


		// ベクトルの正規化処理
		float normalizeMagnification = 1 / sqrt(
			m_direction.x * m_direction.x +
			m_direction.y * m_direction.y +
			m_direction.z * m_direction.z);
		m_direction *= normalizeMagnification;
		// ここまで

		pos += m_direction * m_itemspeed * delta;	// 移動の計算
		float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // 回転の計算

		m_transform->SetPosition(pos); // 移動処理
		m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理


		//auto transComp = GetComponent<Transform>();

		////Itemがプレイヤーに触ってたら消す
		//if ()
		//{
		//	delete ~Item();
		//	/*return ;*/
		//} 		
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
