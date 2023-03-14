/*!
@file Item.h
@brief アイテムの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	float m_moveSpeed;
	float m_pickUpArea;
	bool m_inArea;

	class Item : public GameObject
	{
	public:
		Item(const std::shaerd_ptr<Stage>& stage) :
			GameObject(stage),
			m_moveSpeed(500.0f),
			m_pickUpArea(400.0f),
			m_inArea(false)
		{
		}

		void OnCreate() override;
	};

}
//end basecross
