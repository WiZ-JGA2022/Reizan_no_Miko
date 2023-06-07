/**
@file TimeNumber.h
@brief 制限時間UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TimeNumber : public GameObject {
		// スキップボタン
		const WORD BUTTON_TIMESKIP = XINPUT_GAMEPAD_RIGHT_SHOULDER;
				
		const Vec2 m_NumberSize; // 大きさ
		const int m_OneMinite; // 一分

		int m_place; // 桁数

		float m_totalTime; // 制限時間
		int m_minutes; // 分
		float m_seconds; // 秒
		float m_oldSeconds; // 直前の時間

		float m_timeSkip; // 残り時間のスキップ
		bool m_skipFlag; // スキップのフラグ

		bool m_isPlay; // 
		bool m_startCountDown; // カウントダウン
		
		vector<shared_ptr<NumberUI>> m_numbers; // 数字
		shared_ptr<SoundItem> m_se; // se用

	public:
		// コンストラクタ
		TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay, const bool skipFlag);
		// デストラクタ
		~TimeNumber();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
		// 描画処理
		void OnDraw() override;

		void UpdateValue(int minites, float seconds);
		float GetTimeLeft();
		float GetSkipTime()
		{
			return m_timeSkip;
		}

	};
}