/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int m_BaseRisingValue; // ステータスの基礎上昇量

        int m_expLevel;         // 経験値レベル
        float m_expCount;       // 経験値取得量
        float m_maxExp;         // 必要経験値
        float m_previousExp;    // 前回必要経験値
        
        // ステータス名
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"}
        };

        // ステータス値
        std::map<wstring, float> m_statusValue = {
            {L"HP", 50.0f},
            {L"ATK", 20.0f},
            {L"DEF", 1.0f},
            {L"SPD", 3.0f},
            {L"HASTE", 1.0f},
            {L"PICKUP", 100.0f}
        };

        // ステータスレベル
        std::map<wstring, int> m_statusLevel = {
            {L"HP", 0},
            {L"ATK", 0},
            {L"DEF", 0},
            {L"SPD", 0},
            {L"HASTE", 0},
            {L"PICKUP", 0}
        };

        vector<float> m_statusRisingValue; // ステータス上昇量

    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage) :
            GameObject(stage),
            m_BaseRisingValue(10),
            m_expLevel(1),
            m_expCount(0.0f),
            m_maxExp(10.0f),
            m_previousExp(10.0f)
        {
        } 
        void OnCreate() override;
        void OnUpdate() override;

        float GetStatusValue(wstring m_statusName);

        void PlayerDamageProcess();

        void StatusLevelUpdate(int selectStatusNum);

    };

}
