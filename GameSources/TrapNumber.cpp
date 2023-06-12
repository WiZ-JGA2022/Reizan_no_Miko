/**
@file TrapNumber.cpp
@brief 罠を置ける数を数字で表示するUI
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//コンストラクタとデストラクタ
	TrapNumber::TrapNumber(const shared_ptr<Stage>& stage) :
		GameObject(stage),
		m_place(5)
	{
	}
	TrapNumber::~TrapNumber() {}
	//終了

	//初期化
	void TrapNumber::OnCreate()
	{
		for (int i = 0; i < 4; i++)
		{
			m_numbers[i].reserve(m_place);

			for (int j = 0; j < m_place; j++)
			{
				auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_Size, L"TRAP_NUMBER"); // オブジェクトを生成するけどステージに追加しない
				numberObj->SetPosition(Vec2((220.0f + (270.0f * i)) - m_Size.x * j, 0.0f), -0.42f); // 画面の右端から、スコアのすべての桁が収まる位置に調整する
				m_numbers[i].push_back(numberObj);
			}
		}
	}

	//更新処理
	void TrapNumber::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		for (int i = 0; i < 2; i++)
		{
			UpdateValue(player->GetTrapLimit(i), player->GetTrapLimit(i) - player->GetTrapCount(i), i);
		}

		if (player->GetCondition() == 1) {
			// 処理終了後に表示した画像を消す処理

			GetStage()->RemoveGameObject<TrapNumber>(GetThis<TrapNumber>());

		}
	}

	//描画処理
	void TrapNumber::OnDraw()
	{
		for (int i = 0; i < 2; i++) // 2は将来的に4にする
		{
			for (auto& number : m_numbers[i])
			{
				number->OnDraw();
			}
		}
	}

	void TrapNumber::UpdateValue(int trapLimit, int currentTrapCount, int index)
	{
		int place = 1;
		for (auto& numberObj : m_numbers[index])
		{
			int maxNumber = trapLimit / place % 10; // 1桁目から表示
			int currentNumber = currentTrapCount * 1000 / place % 10; // 4桁目以降に表示
			int srash = 10;
			if (place == 100)
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