/*!
@file PlayerStatusController.h
@brief �v���C���[�̃X�e�[�^�X���Ǘ�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        //�G�t�F�N�g
        shared_ptr<EfkEffect> m_EfkEffect;
        //�G�t�F�N�g���s�I�u�W�F�N�g
        shared_ptr<EfkPlay> m_EfkPlay;
        
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
        const float m_DefaultStatusValue[7] = {
            50.0f,
            5.0f,
            1.0f,
            3.0f,
            1.0f,
            3.0f
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

    public:
        // �R���X�g���N�^
        PlayerStatusController(const std::shared_ptr<Stage>& stage);
        // �f�X�g���N�^
        ~PlayerStatusController();
        // ������
        void OnCreate() override;
        // �X�V����
        void OnUpdate() override;

        /**
        * �v���C���[�ɗ^����_���[�W���v�Z����֐�
        * 
        * @param damage �^����_���[�W��
        */
        void PlayerDamageProcess(float damage);

        /**
        * �X�e�[�^�X�̒l���擾����֐�
        *
        * @param statusKey �擾����X�e�[�^�X�̖��O
        *
        * @return �w�肵���X�e�[�^�X�̒l
        */
        float GetStatusValue(wstring statusKey)
        {
            return m_statusValue[statusKey];
        }

        /**
        * HP������擾����֐�
        *
        * @return HP���
        */
        int GetMaxHp()
        {
            return (int)m_DefaultStatusValue[0];
        }

    };

}
