/**
@file HpNumber.cpp
@brief 現在HPと最大HPを数字で表示するUIの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	HpNumber::HpNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(7),
		m_maxHp(0)
	{
	}
	HpNumber::~HpNumber() {}

	void HpNumber::OnCreate()
	{
		//m_numbers.reserve(m_place);

		//for (int i = 0; i < m_place; i++)
		//{
		//	auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"HP_NUMBER"); // オブジェクトを生成するけどステージに追加しない
		//	numberObj->SetPosition(Vec2(App::GetApp()->GetGameWidth() + 400.0f + m_Size.x * i, 0.0f), 0.49f); // 画面の右端から、スコアのすべての桁が収まる位置に調整する
		//	m_numbers.push_back(numberObj);
		//}

	}

	//void HpNumber::OnUpdate()
	//{
	//	auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
	//	if (levelUpEvent->GetEventActive())
	//	{
	//		return;
	//	}

	//	auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

	//	if (m_maxHp < playerStatus->GetStatusValue(L"HP"))
	//	{
	//		m_maxHp = playerStatus->GetStatusValue(L"HP");
	//	}
	//	UpdateValue(m_maxHp, true);
	//	UpdateValue(playerStatus->GetStatusValue(L"HP"), false);
	//}

	//void HpNumber::OnDraw()
	//{
	//	//for (auto& number : m_numbers)
	//	//{
	//	//	number->OnDraw();
	//	//}
	//}

	//void HpNumber::UpdateValue(float Hp, bool isMax)
	//{
	//	//if (isMax)
	//	//{
	//	//	int place = 10000; 
	//	//	for (auto& numberObj : m_numbers)
	//	//	{
	//	//		int number = (int)Hp / place % 10; // スコアの値から指定の「位」を削り、その時に1の位を余りとして残す
	//	//		numberObj->SetNumber(number); // 現在の桁が表す数値を元にナンバーオブジェクトの表示内容を設定する

	//	//		place *= 10; // 桁をずらす
	//	//	}

	//	//}
	//	//else
	//	//{
	//	//	int place = 1;
	//	//	for (auto& numberObj : m_numbers)
	//	//	{
	//	//		int number = (int)Hp / place % 10; // スコアの値から指定の「位」を削り、その時に1の位を余りとして残す
	//	//		numberObj->SetNumber(number); // 現在の桁が表す数値を元にナンバーオブジェクトの表示内容を設定する

	//	//		place *= 10; // 桁をずらす
	//	//	}
	//	//}
	//}
}