/*!
@file Field.h
@brief 地面を表すクラスを定義する
@prod 矢吹悠葉
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Field : public GameObject
	{
	public:
		// コンストラクタ
		Field(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
	};

	class KeyStone : public GameObject
	{
		const int m_DefaultDelay; // ダメージを受ける間隔
		const float m_DefaultHp = 100.0f; // 初期HP
		
		float m_hp; // 現在HP
		int m_delay;
		bool m_broken; // 壊れたかどうか

	public:
		// コンストラクタ
		KeyStone(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultDelay(5),
			m_delay(0),
			m_hp(m_DefaultHp),
			m_broken(false)
		{
		}

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;

		// ダメージ処理
		void DamageProcess();

		// 最大HPを取得する
		int GetMaxHp()
		{
			return (int)m_DefaultHp;
		}
		// 現在のHPを取得する
		float GetCurrentHp()
		{
			return m_hp;
		}
	};
}

//end basecross

