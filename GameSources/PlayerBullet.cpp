/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include <time.h>

namespace basecross {

    void PlayerBullet::OnCreate()
    {
        Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
        spanMat.affineTransformation(
            Vec3(1.0f, 1.0f, 1.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f)
        );
        //影をつける（シャドウマップを描画する）
        auto ptrShadow = AddComponent<Shadowmap>();
        //影の形（メッシュ）を設定
        ptrShadow->SetMeshResource(L"OHUDA");
        ptrShadow->SetMeshToTransformMatrix(spanMat);

        auto drawComp = AddComponent<BcPNTStaticModelDraw>();
        drawComp->SetFogEnabled(false);
        drawComp->SetMeshResource(L"OHUDA");
        drawComp->SetMeshToTransformMatrix(spanMat);

        // オーナーの向きをベクトルで取得しておく
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // 前方向を示すベクトル
        // コリジョンをつける
        auto ptrColl = AddComponent<CollisionObb>();
        // 衝突判定はAuto
        ptrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"PlayerBullet");
    
        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // オーナーと重ならないように、進行方向に少しずらす
        m_transform->SetQuaternion(ownerTrans->GetQuaternion());
        m_transform->SetScale(Vec3(0.5f));

    }

    void PlayerBullet::OnUpdate()
    {
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // レベルアップイベント実行中またはプレイヤーが居ないとき
        if (!player->GetDrawActive())
        {
            // 処理を停止する
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_transform->SetPosition(pos);
        
        // 弾が遠くに行ったら消す
        if (pos.length() > 70.0f)
        {
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
        }
    }

    void PlayerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
    {
        // 敵にあたったら
        if (other->FindTag(L"Enemy"))
        {
            // 消す
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
            return;
        }
    }

}
