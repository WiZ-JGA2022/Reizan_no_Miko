/*!
@file EnemyBullet.cpp
@brief 敵の弾　実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    void EnemyBullet::OnCreate()
    {
        auto ptrColl = AddComponent<CollisionSphere>();
        // 衝突判定はNone
        ptrColl->SetAfterCollision(AfterCollision::None);

        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");
        drawComp->SetEmissive(Col4(0.4f, 0.6f, 0.9f, 1.0f));

        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(m_position);
        m_transform->SetScale(m_scale);

        MoveEnemyBullet();
    }

    void EnemyBullet::OnUpdate()
    {
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // プレイヤーが居なかったら
        if (!player->GetDrawActive())
        {
            // 処理を停止する
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        m_position += m_direction * m_speed * delta; // 移動の計算

        m_transform->SetPosition(m_position); // 移動処理

        auto playerPosition = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>()->GetPosition();
        // if (playerPosition.length() - m_position.length() > 10.0f || -10.0f > playerPosition.length() - m_position.length())
        if (playerPosition.y < -10.0f)
        {
            GetStage()->RemoveGameObject<EnemyBullet>(GetThis<EnemyBullet>());
        }
    }

    void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
    {
        if (other->FindTag(L"Player"))
        {
            auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
            playerStatus->PlayerDamageProcess(m_damage);
            GetStage()->RemoveGameObject<EnemyBullet>(GetThis<EnemyBullet>());
        }
        if (other->FindTag(L"STAGE"))
        {
            GetStage()->RemoveGameObject<EnemyBullet>(GetThis<EnemyBullet>());
        }
    }

    void EnemyBullet::MoveEnemyBullet()
    {
        // デルタタイムの取得
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        // ベクトルの取得
        auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
        auto playerPos = playerTrans->GetPosition(); // プレイヤーの位置を取得

        m_direction = playerPos - m_position; // プレイヤーとの距離を計算

        // ベクトルの正規化処理
        float normalizeMagnification = 1 / sqrt(
            m_direction.x * m_direction.x +
            m_direction.y * m_direction.y +
            m_direction.z * m_direction.z);
        m_direction *= normalizeMagnification;
        // ここまでw

        float rotationY = atan2f(-m_direction.z, m_direction.x); // 回転の計算
        m_transform->SetRotation(Vec3(0, rotationY, 0)); // 回転処理
    }
}
//end basecross
