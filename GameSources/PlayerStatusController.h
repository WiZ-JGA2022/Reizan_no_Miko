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

        int m_expLevel;          // Level
        float m_expCount;     // �o���l�擾��
        float m_maxExp;      // �K�v�o���l
        float m_previousExp; // �O��K�v�o���l
        
        std::map<int, wstring> statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"}
        };

        std::map<wstring, float> statusValue = {
            {L"HP", 100.0f},
            {L"ATK", 1.0f},
            {L"DEF", 1.0f},
            {L"SPD", 1.0f},
            {L"HASTE", 1.0f},
            {L"PICKUP", 1.0f}
        };

        std::map<wstring, int> statusLevel = {
            {L"HP", 0},
            {L"ATK", 0},
            {L"DEF", 0},
            {L"SPD", 0},
            {L"HASTE", 0},
            {L"PICKUP", 0}
        };

        // �X�e�[�^�X�ۑ��p
        vector<float> status;
        float maxHp;


    public:
        PlayerStatusController(const std::shared_ptr<Stage>& stage) :
            GameObject(stage),
            MAGNIFICATION(10),
            m_expLevel(1),
            m_expCount(0.0f),
            m_maxExp(10.0f),
            m_previousExp(10.0f),
            maxHp(0.0f)
        {
        } 
        void OnCreate() override;
        void OnUpdate() override;

        void StatusLevelUpdate(int selectStatusNum);

    };

}
