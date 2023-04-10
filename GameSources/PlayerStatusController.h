/*!
@file PlayerStatusController.h
@brief �v���C���[�̃X�e�[�^�X���Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        const int m_BaseRisingValue; // �X�e�[�^�X�̊�b�㏸��
        const int m_DamageDelayCount; // �_���[�W���󂯂�Ԋu

        int m_maxHp;
        int m_maxExp; // �K�v�o���l
        int m_beforeMaxExp; // �O��K�v�o���l
                
        int m_damageDelayFlame; // �_���[�W���󂯂�Ԋu
        
        // �X�e�[�^�X��
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"},
            {6, L"EXP"}
        };

        // �X�e�[�^�X�l�̏����l
        const float m_DefaultStatusValue[7] = {
            50.0f,
            10.0f,
            1.0f,
            3.0f,
            1.0f,
            3.0f,
            0.0f
        };
        // �X�e�[�^�X�l
        std::map<wstring, float> m_statusValue = {
            {L"HP", m_DefaultStatusValue[0]},
            {L"ATK", m_DefaultStatusValue[1]},
            {L"DEF", m_DefaultStatusValue[2]},
            {L"SPD", m_DefaultStatusValue[3]},
            {L"HASTE", m_DefaultStatusValue[4]},
            {L"PICKUP", m_DefaultStatusValue[5]},
            {L"EXP", m_DefaultStatusValue[6]}
        };

        // �X�e�[�^�X���x��
        std::map<wstring, int> m_statusLevel = {
            {L"HP", 0},
            {L"ATK", 0},
            {L"DEF", 0},
            {L"SPD", 0},
            {L"HASTE", 0},
            {L"PICKUP", 0},
            {L"EXP", 0}
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

        int GetMaxHp();
        int GetMaxExp();

        /**
        * �v���C���[�ɗ^����_���[�W���v�Z����֐�
        * 
        * @param damage �^����_���[�W��
        */
        void PlayerDamageProcess(float damage);

        /**
        * �X�e�[�^�X����������֐�
        * 
        * @param selectStatusNum ��������X�e�[�^�X�ԍ�
        */
        void StatusLevelUpdate(int selectStatusNum);

        /**
        * �w�肵��������EXP�𑝂₷�֐�
        *
        * @param expValue ���₷EXP�̐�
        */
        void ExpValueUpdate(int expValue);
    };

}
