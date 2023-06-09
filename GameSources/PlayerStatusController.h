/*!
@file PlayerStatusController.h
@brief プレイヤーのステータスを管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class PlayerStatusController : public GameObject
    {
        //エフェクト
        shared_ptr<EfkEffect> m_EfkEffect;
        //エフェクト実行オブジェクト
        shared_ptr<EfkPlay> m_EfkPlay;
        
        // ステータス名
        std::map<int, wstring> m_statusName = {
            {0, L"HP"},
            {1, L"ATK"},
            {2, L"DEF"},
            {3, L"SPD"},
            {4, L"HASTE"},
            {5, L"PICKUP"}
        };

        // ステータス値の初期値
        const float m_DefaultStatusValue[7] = {
            50.0f,
            5.0f,
            1.0f,
            3.0f,
            1.0f,
            3.0f
        };
        // ステータス値
        std::map<wstring, float> m_statusValue = {
            {L"HP", m_DefaultStatusValue[0]},
            {L"ATK", m_DefaultStatusValue[1]},
            {L"DEF", m_DefaultStatusValue[2]},
            {L"SPD", m_DefaultStatusValue[3]},
            {L"HASTE", m_DefaultStatusValue[4]},
            {L"PICKUP", m_DefaultStatusValue[5]}
        };

    public:
        // コンストラクタ
        PlayerStatusController(const std::shared_ptr<Stage>& stage);
        // デストラクタ
        ~PlayerStatusController();
        // 初期化
        void OnCreate() override;
        // 更新処理
        void OnUpdate() override;

        /**
        * プレイヤーに与えるダメージを計算する関数
        * 
        * @param damage 与えるダメージ量
        */
        void PlayerDamageProcess(float damage);

        /**
        * ステータスの値を取得する関数
        *
        * @param statusKey 取得するステータスの名前
        *
        * @return 指定したステータスの値
        */
        float GetStatusValue(wstring statusKey)
        {
            return m_statusValue[statusKey];
        }

        /**
        * HP上限を取得する関数
        *
        * @return HP上限
        */
        int GetMaxHp()
        {
            return (int)m_DefaultStatusValue[0];
        }

    };

}
