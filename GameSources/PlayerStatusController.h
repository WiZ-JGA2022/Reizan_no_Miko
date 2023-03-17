/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int MAGNIFICATION;

        int m_level;          // Level
        float m_expCount;     // 経験値取得量
        float m_maxExp;      // 必要経験値
        float m_previousExp; // 前回必要経験値

        enum eStatusName
        {
            HP,//体力
            ATK,//攻撃力
            DEF,//防御力
            SPD,//移動速度
            HASTE,//攻撃速度
            RANGE,//攻撃範囲
            PICKUP,//収集範囲
        };
        enum eStatusLevel
        {
            HPLv,
            ATKLv,
            DEFLv,
            SPDLv,
            HASTELv,
            RANGELv,
            PICKUPLv,
        };

        std::map<eStatusName, float> statusValue =
        {
            {HP, 100},
            {ATK, 1},
            {DEF, 1},
            {SPD, 1},
            {HASTE, 1},
            {RANGE, 1},
            {PICKUP, 1},
        };

        std::map<eStatusLevel, float> statusLevel =
        {
            { HPLv, 0 },
            { ATKLv, 0 },
            { DEFLv, 0 },
            { SPDLv, 0 },
            { HASTELv, 0 },
            { RANGELv, 0 },
            { PICKUPLv, 0 },
        };

    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage) :
            GameObject(stage),
            MAGNIFICATION(10),
            m_level(1),
            m_expCount(0),
            m_maxExp(10),
            m_previousExp(10)
        {
        } 
        void OnCreate() override;
        inline void OnUpdate() override;
    };

}
