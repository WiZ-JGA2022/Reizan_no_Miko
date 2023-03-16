/*!
@file Item.h
@brief アイテムの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item : public GameObject {

		std::shared_ptr<Transform>m_transform;

		Vec3 m_Xsize;

	public :
		Item(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_Xsize(Vec3(0))
		{
		}
		void OnCreate() override;
	};

}
//end basecross
