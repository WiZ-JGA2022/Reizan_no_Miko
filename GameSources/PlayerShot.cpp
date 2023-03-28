/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include <time.h>

namespace basecross {

    void PlayerShot::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");
        
        // オーナーの向きをベクトルで取得しておく
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // 前方向を示すベクトル
    
        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // オーナーと重ならないように、進行方向に少しずらす
        m_Transform->SetScale(Vec3(0.5f));

    }

    void PlayerShot::OnUpdate()
    {
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);

        
        // 弾が遠くに行ったら消す
        if (pos.length() > 50.0f)
        {
            GetStage()->RemoveGameObject<PlayerShot>(GetThis<PlayerShot>());
        }


    }

    void PlayerHomingShot::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");

        // オーナーの向きをベクトルで取得しておく
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // 前方向を示すベクトル

        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // オーナーと重ならないように、進行方向に少しずらす
        m_Transform->SetScale(Vec3(0.5f));

    }

    void PlayerHomingShot::OnUpdate()
    {
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);

    }

}
