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
		void OnUpdate();
	};
	class Field2 : public GameObject
	{
		Vec3 m_position;

	public:
		Field2(const std::shared_ptr<Stage>& stage, const Vec3& position) :
			GameObject(stage),
			m_position(position)
		{
		}

		void OnCreate();
		void OnUpdate();
	};
}
//end basecross

