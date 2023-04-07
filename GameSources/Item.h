/*!
@file Item.h
@brief アイテムの定義
*/

#pragma once
#include "stdafx.h"
#include "PlayerController.h"

namespace basecross {
	class Item : public GameObject
	{
	
		  std::shared_ptr<PlayerController> m_player;
		 shared_ptr<Transform>m_transform; 

		Vec3 m_itemPosition;
		Vec3 m_itemScale;
		Vec3 m_direction; // プレイヤーへの方向

		float m_attractX;
		float m_attractZ;
		float m_itemspeed;
		float m_inArea;
		bool m_enemydis;

	public:
		Item(const shared_ptr<Stage>& stagePtr, std::shared_ptr<PlayerController>& playerPtr) :
			GameObject(stagePtr),
			m_player(playerPtr),
			m_itemScale(0.5f,0.5f,0.5f),
			m_itemPosition(3.0f,0.0f,3.0f),
			m_itemspeed(1.0f),
			m_attractX(1.0f),
			m_attractZ(1.0f),
			m_inArea(10.0f),
			m_enemydis(false)
		{
		};

	public:
		//Item(const shared_ptr<Stage>& stage);
		//Item(const shared_ptr<Stage>& stage,
		//	const Vec3& m_itemPosition);
		//~Item();
		
		void OnCreate() override;
		void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

	};


}//end basecross
