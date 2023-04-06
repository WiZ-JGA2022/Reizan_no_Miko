/*!
@file EnemyBullet.cpp
@brief �G�̒e�@����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    void EnemyBullet::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");

        // �I�[�i�[�̌������x�N�g���Ŏ擾���Ă���
        auto ownerTrans = m_owner->GetComponent<Transform>();
        
        m_forward = ownerTrans->GetForward(); // �O�����������x�N�g��

        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f);
        m_Transform->SetScale(Vec3(0.5f));

    }

    void EnemyBullet::OnUpdate()
    {
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);

    }
}
//end basecross
