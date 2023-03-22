/*!
@file WeaponStatus.h
@brief �v���C���[�L����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class WeaponStatus_bill : public GameObject
	{
        enum eStatusName
        {
            ATK,//�U����
            SPD,//�ړ����x
            HASTE,//�U�����x
            RANGE,//�U���͈�
        };
        enum eStatusLevel
        {
            ATKLv,
            SPDLv,
            HASTELv,
            RANGELv,
        };

        std::map<eStatusName, float> statusValue =
        {
            {ATK, 1},
            {SPD, 1},
            {HASTE, 1},
            {RANGE, 1},
        };

        std::map<eStatusLevel, float> statusLevel =
        {
            { ATKLv, 0 },
            { SPDLv, 0 },
            { HASTELv, 0 },
            { RANGELv, 0 },
        };

	public:
		WeaponStatus_bill (const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V

	};

	class WeaponStatus_barrier : public GameObject
	{
        enum eStatusName
        {
            ATK,//�U����
            SPD,//�ړ����x
            HASTE,//�U�����x
            RANGE,//�U���͈�
        };
        enum eStatusLevel
        {
            ATKLv,
            SPDLv,
            HASTELv,
            RANGELv,
        };

        std::map<eStatusName, float> statusValue =
        {
            {ATK, 1},
            {SPD, 1},
            {HASTE, 1},
            {RANGE, 1},
        };

        std::map<eStatusLevel, float> statusLevel =
        {
            { ATKLv, 0 },
            { SPDLv, 0 },
            { HASTELv, 0 },
            { RANGELv, 0 },
        };

	public:
		WeaponStatus_barrier(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V

	};
	class WeaponStatus_trackingbullets : public GameObject
	{
        enum eStatusName
        {
            ATK,//�U����
            SPD,//�ړ����x
            HASTE,//�U�����x
            RANGE,//�U���͈�
        };
        enum eStatusLevel
        {
            ATKLv,
            SPDLv,
            HASTELv,
            RANGELv,
        };

        std::map<eStatusName, float> statusValue =
        {
            {ATK, 1},
            {SPD, 1},
            {HASTE, 1},
            {RANGE, 1},
        };

        std::map<eStatusLevel, float> statusLevel =
        {
            { ATKLv, 0 },
            { SPDLv, 0 },
            { HASTELv, 0 },
            { RANGELv, 0 },
        };

	public:
		WeaponStatus_trackingbullets(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // �I�u�W�F�N�g�̏����ݒ�p�̊֐�
		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V

	};

}
