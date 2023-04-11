/**
@file ExpNumber.cpp
@brief 現在EXPと最大EXPを数字で表示するUIの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ExpNumber::ExpNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(7),
		m_maxExp(0)
	{
	}
	ExpNumber::~ExpNumber() {}

	void ExpNumber::OnCreate()
	{
		m_numbers.reserve(m_place);

		for (int i = 0; i < m_place; i++)
		{
			auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"EXP_NUMBER"); // オブジェクトを生成するけどステージに追加しない
			numberObj->SetPosition(Vec2(480.0f - m_Size.x * i, 0.0f), 0.46f); // 画面の右端から、スコアのすべての桁が収まる位置に調整する
			m_numbers.push_back(numberObj);
		}
	}

	void ExpNumber::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetEventActive())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		UpdateValue(playerStatus->GetMaxExp(), playerStatus->GetStatusValue(L"EXP"));
	}

	void ExpNumber::OnDraw()
	{
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}

	void ExpNumber::UpdateValue(int maxExp, float currentExp)
	{
		int place = 1;
		for (auto& numberObj : m_numbers)
		{
			int currentNumber = (int)currentExp * 10000 / place % 10; // 4桁目以降に表示
			int maxNumber = maxExp / place % 10; // 1桁目から表示
			int srash = 10;
			if (place == 1000)
			{
				numberObj->SetNumber(srash); // 3桁目にスラッシュを表示
			}
			else
			{
				numberObj->SetNumber(currentNumber + maxNumber); // 現在の桁が表す数値を元にナンバーオブジェクトの表示内容を設定する
			}

			place *= 10; // 桁をずらす
		}
	}
}
