/*!
@file Item.cpp
@brief �A�C�e���̎���
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

		auto ItemColl = AddComponent<CollisionSphere>();

		//Enemy����������o��
		//auto EnemyOut = m_enemydis;
		
		transComp->SetPosition(m_itemPosition);

		//if (EnemyOut&&)
		//{
		//	//GetStage()->AddGameObject<Item>(m_itemPosition);
		//	//GetStage()->AddGameObject<Item>(GetThis<EnemyController>());
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

		auto transComp = GetComponent<Transform>();
		auto Itempos = transComp->GetPosition();

		auto playerTrans = m_player->GetComponent<Transform>();
		auto Playerpos = playerTrans->GetPosition();

		//���͈̔͂Ƀv���C���[���������炻�̕����Ɉړ�����
		//auto ItemAreapos = m_inArea;
		//bool IteminArea(false)
		//	if (Playerpos > ItemAreapos && IteminArea)
		//	{
		//		
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

		////Item���v���C���[�ɐG���Ă������
		//if ()
		//{
		//	delete ~Item();
		//	/*return ;*/
		//} 
		
		if (Itempos.length() < Playerpos.x)//�܂�player�̔���͂ł��ĂȂ��̂�1.0�����Ă���
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}
		if (Itempos.length() < Playerpos.z)//�܂�player�̔���͂ł��ĂȂ��̂�1.0�����Ă���
		{
			GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		}

	}

}
//end basecross
