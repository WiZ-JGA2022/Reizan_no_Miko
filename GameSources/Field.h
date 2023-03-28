/*!
@file Field.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Field : public GameObject
	{
	public:
		Field(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
	};

}
//end basecross

