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
        const int m_DelayCount; // �_���[�W���󂯂�Ԋu

        int m_expLevel;         // �o���l���x��
        float m_expCount;       // �o���l�擾��
        float m_maxExp;         // �K�v�o���l
        float m_previousExp;    // �O��K�v�o���l
        float m_enemyATK; // �G�̍U����
        
        int m_delayFlame; // �_���[�W���󂯂�Ԋu
        
        // �X�e�[�^�X��
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"}
        };

        // �X�e�[�^�X�l�̏����l
        const float m_DefaultStatusValue[6] = {
            50.0f,
            10.0f,
            1.0f,
            3.0f,
            1.0f,
            100.0f
        };
        // �X�e�[�^�X�l
        std::map<wstring, float> m_statusValue = {
            {L"HP", m_DefaultStatusValue[0]},
            {L"ATK", m_DefaultStatusValue[1]},
            {L"DEF", m_DefaultStatusValue[2]},
            {L"SPD", m_DefaultStatusValue[3]},
            {L"HASTE", m_DefaultStatusValue[4]},
            {L"PICKUP", m_DefaultStatusValue[5]}
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
        PlayerStatusController(const std::shared_ptr<Stage>& stage);
        ~PlayerStatusController();
        void OnCreate() override;
        void OnUpdate() override;

        /**
        * �X�e�[�^�X�̒l���擾����֐�
        * 
        * @param statusKey �擾����X�e�[�^�X�̖��O
        * 
        * @return �w�肵���X�e�[�^�X�̒l
        */
        float GetStatusValue(wstring statusKey);

        /**
        * �v���C���[���󂯂��_���[�W���v�Z����֐�
        */
        void PlayerDamageProcess();

        /**
        * �X�e�[�^�X����������֐�
        * 
        * @param selectStatusNum ��������X�e�[�^�X�ԍ�
        */
        void StatusLevelUpdate(int selectStatusNum);

        /**
        * �G�̍U���͂�ݒ肷��֐�
        */
        void SetEnemyATK(float ATK);
    };

}
