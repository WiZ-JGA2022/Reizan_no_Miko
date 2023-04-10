/*!
@file PlayerStatusController.h
@brief プレイヤーのステータスを管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int m_BaseRisingValue; // ステータスの基礎上昇量
        const int m_DamageDelayCount; // ダメージを受ける間隔

        int m_maxHp;
        int m_maxExp; // 必要経験値
        int m_beforeMaxExp; // 前回必要経験値
                
        int m_damageDelayFlame; // ダメージを受ける間隔
        
        // ステータス名
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"},
            {6, L"EXP"}
        };

        // ステータス値の初期値
        const float m_DefaultStatusValue[7] = {
            50.0f,
            10.0f,
            1.0f,
            3.0f,
            1.0f,
            3.0f,
            0.0f
        };
        // ステータス値
        std::map<wstring, float> m_statusValue = {
            {L"HP", m_DefaultStatusValue[0]},
            {L"ATK", m_DefaultStatusValue[1]},
            {L"DEF", m_DefaultStatusValue[2]},
            {L"SPD", m_DefaultStatusValue[3]},
            {L"HASTE", m_DefaultStatusValue[4]},
            {L"PICKUP", m_DefaultStatusValue[5]},
            {L"EXP", m_DefaultStatusValue[6]}
        };

        // ステータスレベル
        std::map<wstring, int> m_statusLevel = {
            {L"HP", 0},
            {L"ATK", 0},
            {L"DEF", 0},
            {L"SPD", 0},
            {L"HASTE", 0},
            {L"PICKUP", 0},
            {L"EXP", 0}
        };

        vector<float> m_statusRisingValue; // ステータス上昇量

    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage);
        ~PlayerStatusController();
        void OnCreate() override;
        void OnUpdate() override;

        /**
        * ステータスの値を取得する関数
        * 
        * @param statusKey 取得するステータスの名前
        * 
        * @return 指定したステータスの値
        */
        float GetStatusValue(wstring statusKey);

        int GetMaxHp();
        int GetMaxExp();

        /**
        * プレイヤーに与えるダメージを計算する関数
        * 
        * @param damage 与えるダメージ量
        */
        void PlayerDamageProcess(float damage);

        /**
        * ステータスを強化する関数
        * 
        * @param selectStatusNum 強化するステータス番号
        */
        void StatusLevelUpdate(int selectStatusNum);

        /**
        * 指定した数だけEXPを増やす関数
        *
        * @param expValue 増やすEXPの数
        */
        void ExpValueUpdate(int expValue);
    };

}
