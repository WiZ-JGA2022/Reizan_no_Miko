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

	class KeyStone : public GameObject
	{
		const int m_DefaultDelay;
		const float m_DefaultHp = 100.0f;
		
		float m_hp;
		int m_delay;
		bool m_broken;

	public:
		KeyStone(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultDelay(5),
			m_delay(0),
			m_hp(m_DefaultHp),
			m_broken(false)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void DamageProcess();

		int GetMaxHp()
		{
			return (int)m_DefaultHp;
		}
		float GetCurrentHp()
		{
			return m_hp;
		}
	};
}

//end basecross

