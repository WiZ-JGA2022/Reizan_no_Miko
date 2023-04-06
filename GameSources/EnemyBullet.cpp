/*!
@file EnemyBullet.cpp
@brief 敵の弾　実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    void EnemyBullet::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");

        // オーナーの向きをベクトルで取得しておく
        auto ownerTrans = m_owner->GetComponent<Transform>();
        
        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(ownerTrans->GetPosition());
        m_transform->SetScale(Vec3(0.5f));


        MoveEnemyBullet();

    }

    void EnemyBullet::OnUpdate()
    {
        auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
        if (levelUpEvent->GetControllerSprite())
        {
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        m_position += m_direction * m_speed * delta;// 移動の計算

        m_transform->SetPosition(m_position); // 移動処理
    }

    Vec3 EnemyBullet::MoveEnemyBullet()
    {
        // デルタタイムの取得
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        // 各種ベクトルの取得
        auto pos = m_transform->GetPosition(); // 自身の位置ベクトルを取得
        auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
        auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置ベクトルを取得

        m_direction = playerPos - pos; // プレイヤーへの方向を計算

        // ベクトルの正規化処理
        float normalizeMagnification = 1 / sqrt(
            m_direction.x * m_direction.x +
            m_direction.y * m_direction.y +
            m_direction.z * m_direction.z);
        m_direction *= normalizeMagnification;
        // ここまで

        //pos += m_direction * m_speed * delta;	// 移動の計算
        float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // 回転の計算

        //m_transform->SetPosition(pos); // 移動処理
        m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理

        return m_direction;
    }

}
//end basecross
