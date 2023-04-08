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
		Vec3 m_itemPosition;
		Vec3 m_itemScale;
		Vec3 m_direction;

		float m_speed;
		float m_attractX;
		float m_attractZ;
		//float m_inArea;

		shared_ptr<Transform> m_transform;

	public:
		Item(const shared_ptr<Stage>& stagePtr) :
			GameObject(stagePtr),
			m_itemPosition(1.0f, 0.0f, 1.0f),
			m_itemScale(0.5f,0.5f,0.5f),
			m_speed(1.0f),
			m_attractX(1.0f),
			m_attractZ(1.0f)
			//m_inArea(10.0f)
		{
		};

		void OnCreate() override;
		void OnUpdate() override;
		
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};

}//end basecross
