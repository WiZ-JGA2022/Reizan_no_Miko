/*!
@file EnemyController.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {

    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage) :
            GameObject(stage)
        {
        }
    };

    enum eStatusName
    {
        HP,//‘Ì—Í
        ATK,//UŒ‚—Í
        DEF,//–hŒä—Í
        SPD,//ˆÚ“®‘¬“x
        HASTE,//UŒ‚‘¬“x
        RANGE,//UŒ‚”ÍˆÍ
        PICKUP,//ûW”ÍˆÍ
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

    std::map<eStatusName, float> statusValue
    {
        {HP, 100},
        {ATK, 1},
        {DEF, 1},
        {SPD, 1},
        {HASTE, 1},
        {RANGE, 1},
        {PICKUP, 1},
    };

    std::map<eStatusLevel, float> statusLevel
    {
        { HPLv, 0 },
        { ATKLv, 0 },
        { DEFLv, 0 },
        { SPDLv, 0 },
        { HASTELv, 0 },
        { RANGELv, 0 },
        { PICKUPLv, 0 },
    };


}
