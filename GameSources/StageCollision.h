/*!
@file StageCollision.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollision : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision(const std::shared_ptr<Stage>& stage,const Vec3& potision);
		~StageCollision();

		

		void OnCreate() override;
		void OnUpdate() override;
	};

	class StageCollision2 : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision2(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision2();



		void OnCreate() override;
		void OnUpdate() override;
	};

	class StageCollision3 : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision3(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision3();



		void OnCreate() override;
		void OnUpdate() override;
	};
}