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
		Vec3 m_scale;

	public:
		StageCollision(const std::shared_ptr<Stage>& stage,const Vec3& potision,const Vec3& scale);
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

	class StageCollision4 : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision4(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision4();



		void OnCreate() override;
		void OnUpdate() override;
	};

	class StageCollision5 : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision5(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision5();



		void OnCreate() override;
		void OnUpdate() override;
	};

	class StageCollision6 : public GameObject
	{
	
		Vec3 m_position;

	public:
		StageCollision6(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision6();



		void OnCreate() override;
		void OnUpdate() override;
	};

	class StageCollision7 : public GameObject
	{

		Vec3 m_position;

	public:
		StageCollision7(const std::shared_ptr<Stage>& stage, const Vec3& potision);
		~StageCollision7();



		void OnCreate() override;
		void OnUpdate() override;
	};
}