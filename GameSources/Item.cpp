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

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_itemScale);
		transComp->SetPosition(m_itemPosition);

		auto ItemColl = AddComponent<CollisionSphere>();

	}

	void Item::OnUpdate() {
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto Itempos = transComp->GetPosition();

		auto playerTrans = m_player->GetComponent<Transform>();
		auto Playerpos = playerTrans->GetPosition();

		////一定の範囲にプレイヤーが入ったらその方向に移動する
		//auto ItemAreapos = m_inArea;
		//bool IteminArea(false)
		//	if (Playerpos.x > ItemAreapos)
		//	{

		//	}

		if (Playerpos.x == Itempos.x) { m_attractX = 0; }
		if (Playerpos.x < Itempos.x) { m_attractX = -1; }
		if (Playerpos.x > Itempos.x) { m_attractX = +1; }

		if (Playerpos.z == Itempos.z) { m_attractZ = 0; }
		if (Playerpos.z < Itempos.z) { m_attractZ = -1; }
		if (Playerpos.z > Itempos.z) { m_attractZ = +1; }

		float ItemrotationY = atan2f(Playerpos.z, Playerpos.x);
		float ItemattractX = Itempos.x + m_attractX * delta;
		float ItemattractZ = Itempos.z + m_attractZ * delta;
		transComp->SetRotation(Vec3(0, ItemrotationY + XM_PIDIV2, 0));
		transComp->SetPosition(ItemattractX, Itempos.y, ItemattractZ);

		//Itemがプレイヤーの近くに来たら消す
		if (Itempos.length() <Playerpos.x)//まだplayerの判定はできてないので1.0を入れている
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
		if (Itempos.length() < Playerpos.z)//まだplayerの判定はできてないので1.0を入れている
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}

	}

}
//end basecross
