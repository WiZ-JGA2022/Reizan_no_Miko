/**
@file TimeNumber.cpp
@brief 制限時間UIの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeNumber::TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay, const bool skipFlag) :
		GameObject(stage),
		m_NumberSize(Vec2(24.0f, 48.0f)),
		m_OneMinite(60),
		m_place(5),
		m_totalTime(totalTime),
		m_minutes(0),
		m_seconds(0),
		m_oldSeconds(0),
		m_isPlay(isPlay),
		m_skipFlag(skipFlag),
		m_timeSkip(0)
	
	{
	}
	TimeNumber::~TimeNumber() {}

	void TimeNumber::OnCreate()
	{
		m_numbers.reserve(m_place);

		for (int i = 0; i < m_place; i++)
		{
			auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_NumberSize, L"TIME_NUMBER"); // オブジェクトを生成するけどステージに追加しない
			numberObj->SetPosition(Vec2(680.0f - m_NumberSize.x * i, 0.0f), 0.47f);
			m_numbers.push_back(numberObj);
		}
	}

	void TimeNumber::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");

		// レベルアップイベント実行中またはプレイヤーが居ないとき
		if (!player->GetDrawActive())
		{
			// 処理を停止する
			return;
		}

		// 時間の更新
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		m_totalTime -= delta;

		m_minutes = (int)m_totalTime / m_OneMinite;
		m_seconds = m_totalTime - m_minutes * m_OneMinite;

		if ((int)m_seconds != (int)m_oldSeconds)
		{
			UpdateValue(m_minutes, m_seconds);
		}
		m_oldSeconds = m_seconds;

		if (m_isPlay)
		{
			// 時間切れになったら
			if (m_totalTime <= 1 && player->GetCondition() == 1)
			{
				// クリア
				PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
				return;
			}
		}

		//RBボタンを長押ししたらスキップ
		if (pad.wButtons & BUTTON_TIMESKIP && m_skipFlag)
		{
			m_timeSkip += delta;
			if (m_timeSkip > 3) {
				dynamic_pointer_cast<StandbyStage>(GetStage())->ChangeStage();
			}
		}

	}

	void TimeNumber::OnDraw()
	{
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}

	void TimeNumber::UpdateValue(int minites, float seconds)
	{
		int place = 1;
		for (auto& numberObj : m_numbers)
		{
			int secondsNumber = (int)seconds / place % 10; // 1桁目から表示
			int minitesNumber = minites * 1000 / place % 10; // 4桁目以降から表示
			int coron = 10;
			if (place == 100)
			{
				numberObj->SetNumber(coron); // 3桁目にコロンを表示
			}
			else
			{
				numberObj->SetNumber(secondsNumber + minitesNumber); // 現在の桁が表す数値を元にナンバーオブジェクトの表示内容を設定する
			}

			place *= 10; // 桁をずらす
		}
	}

	float TimeNumber::GetTimeLeft()
	{
		return m_totalTime;
	}
}
