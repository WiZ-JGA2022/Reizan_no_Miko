/*!
@file WeaponStatus.h
@brief プレイヤーキャラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class WeaponStatus_bill : public GameObject
	{
        enum eStatusName
        {
            ATK,//攻撃力
            SPD,//移動速度
            HASTE,//攻撃速度
            RANGE,//攻撃範囲
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

		void OnCreate() override; // オブジェクトの初期設定用の関数
		void OnUpdate() override; // オブジェクトデータの更新

	};

	class WeaponStatus_barrier : public GameObject
	{
        enum eStatusName
        {
            ATK,//攻撃力
            SPD,//移動速度
            HASTE,//攻撃速度
            RANGE,//攻撃範囲
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

		void OnCreate() override; // オブジェクトの初期設定用の関数
		void OnUpdate() override; // オブジェクトデータの更新

	};
	class WeaponStatus_trackingbullets : public GameObject
	{
        enum eStatusName
        {
            ATK,//攻撃力
            SPD,//移動速度
            HASTE,//攻撃速度
            RANGE,//攻撃範囲
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

		void OnCreate() override; // オブジェクトの初期設定用の関数
		void OnUpdate() override; // オブジェクトデータの更新

	};

}
