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
        
        m_forward = ownerTrans->GetForward(); // 前方向を示すベクトル

        // 自分のトランスフォームコンポーネントを取得して座標や大きさを設定する
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition()); 
        m_Transform->SetScale(Vec3(0.5f));

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

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);

    }



}
//end basecross
