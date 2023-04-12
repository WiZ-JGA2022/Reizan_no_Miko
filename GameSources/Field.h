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

	class WallA : public GameObject
	{
	public:
		WallA(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
		void OnUpdate();
	};

	class WallB : public GameObject
	{
	public:
		WallB(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
		void OnUpdate();
	};

	class WallC : public GameObject
	{
	public:
		WallC(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
		void OnUpdate();
	};

	class BoxA : public GameObject
	{
	public:
		BoxA(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
		void OnUpdate();
	};

	class BoxB : public GameObject
	{
	public:
		BoxB(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate();
		void OnUpdate();
	};

}
//end basecross

