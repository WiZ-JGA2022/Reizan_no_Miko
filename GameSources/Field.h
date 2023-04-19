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

		void OnCreate() override;
		void OnUpdate() override;
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

		void OnCreate() override;
		void OnUpdate() override;
	};

	class KeyStone : public GameObject
	{
		const int m_DefaultDelay;

		float m_hp;
		float m_delay;

	public:
		KeyStone(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultDelay(5),
			m_delay(0),
			m_hp(100.0f)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void DamageProcess();
	};
}
//end basecross

