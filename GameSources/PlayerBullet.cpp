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
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");
        
        // オーナーの向きをベクトルで取得しておく
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // 前方向を示すベクトル
        // コリジョンをつける
        auto ptrColl = AddComponent<CollisionObb>();
        // 衝突判定はAuto
        ptrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"PlayerBullet");
    
        auto XAPtr = App::GetApp()->GetXAudio2Manager();
        XAPtr->Start(L"GAMECLEAR_BGM", 1, 0.1f);

        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // オーナーと重ならないように、進行方向に少しずらす
        m_Transform->SetScale(Vec3(0.5f));

    }

    void PlayerBullet::OnUpdate()
    {
        auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // レベルアップイベント実行中またはプレイヤーが居ないとき
        if (levelUpEvent->GetEventActive() || !player->GetDrawActive())
        {
            // 処理を停止する
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);
        
        // 弾が遠くに行ったら消す
        if (pos.length() > 50.0f)
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
