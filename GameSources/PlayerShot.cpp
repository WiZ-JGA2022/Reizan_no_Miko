/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include <time.h>

namespace basecross {

    void PlayerShot::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");
        
        // �I�[�i�[�̌������x�N�g���Ŏ擾���Ă���
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // �O�����������x�N�g��
    
        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // �I�[�i�[�Əd�Ȃ�Ȃ��悤�ɁA�i�s�����ɏ������炷
        m_Transform->SetScale(Vec3(0.5f));

    }

    void PlayerShot::OnUpdate()
    {
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);

        
        // �e�������ɍs���������
        if (pos.length() > 50.0f)
        {
            GetStage()->RemoveGameObject<PlayerShot>(GetThis<PlayerShot>());
        }


    }

    void PlayerHomingShot::OnCreate()
    {
        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");

        // �I�[�i�[�̌������x�N�g���Ŏ擾���Ă���
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // �O�����������x�N�g��

        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // �I�[�i�[�Əd�Ȃ�Ȃ��悤�ɁA�i�s�����ɏ������炷
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
