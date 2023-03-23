/*!
@file EnemyController.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int MAGNIFICATION;

        int m_level;          // Level
        float m_expCount;     // �o���l�擾��
        float m_maxExp;      // �K�v�o���l
        float m_previousExp; // �O��K�v�o���l

        enum eStatusName
        {
            HP,//�̗�
            ATK,//�U����
            DEF,//�h���
            SPD,//�ړ����x
            HASTE,//�U�����x
            RANGE,//�U���͈�
            PICKUP,//���W�͈�
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
            {HP, 100.0f},
            {ATK, 1.0f},
            {DEF, 1.0f},
            {SPD, 1.0f},
            {HASTE, 1.0f},
            {RANGE, 1.0f},
            {PICKUP, 1.0f},
        };

        std::map<eStatusLevel, float> statusLevel =
        {
            {HPLv, 0.0f},
            {ATKLv, 0.0f},
            {DEFLv, 0.0f},
            {SPDLv, 0.0f},
            {HASTELv, 0.0f},
            {RANGELv, 0.0f},
            {PICKUPLv, 0.0f},
        };

    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage) :
            GameObject(stage),
            MAGNIFICATION(10),
            m_level(1),
            m_expCount(0.0f),
            m_maxExp(10.0f),
            m_previousExp(10.0f)
        {
        } 
        void OnCreate() override;
        inline void OnUpdate() override;
    };

}
