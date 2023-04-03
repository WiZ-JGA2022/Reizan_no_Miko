/*!
@file EnemyController.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int m_BaseRisingValue; // �X�e�[�^�X�̊�b�㏸��

        int m_expLevel;         // �o���l���x��
        float m_expCount;       // �o���l�擾��
        float m_maxExp;         // �K�v�o���l
        float m_previousExp;    // �O��K�v�o���l
        
        // �X�e�[�^�X��
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"}
        };

        // �X�e�[�^�X�l
        std::map<wstring, float> m_statusValue = {
            {L"HP", 50.0f},
            {L"ATK", 20.0f},
            {L"DEF", 1.0f},
            {L"SPD", 3.0f},
            {L"HASTE", 1.0f},
            {L"PICKUP", 100.0f}
        };

        // �X�e�[�^�X���x��
        std::map<wstring, int> m_statusLevel = {
            {L"HP", 0},
            {L"ATK", 0},
            {L"DEF", 0},
            {L"SPD", 0},
            {L"HASTE", 0},
            {L"PICKUP", 0}
        };

        vector<float> m_statusRisingValue; // �X�e�[�^�X�㏸��

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
