/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include <time.h>

namespace basecross {

    void PlayerBullet::OnCreate()
    {
        Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
        spanMat.affineTransformation(
            Vec3(1.0f, 1.0f, 1.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f),
            Vec3(0.0f, 0.0f, 0.0f)
        );
        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ptrShadow = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
        ptrShadow->SetMeshResource(L"OHUDA");
        ptrShadow->SetMeshToTransformMatrix(spanMat);

        auto drawComp = AddComponent<BcPNTStaticModelDraw>();
        drawComp->SetFogEnabled(false);
        drawComp->SetMeshResource(L"OHUDA");
        drawComp->SetMeshToTransformMatrix(spanMat);

        // �I�[�i�[�̌������x�N�g���Ŏ擾���Ă���
        auto ownerTrans = m_owner->GetComponent<Transform>();
        m_forward = ownerTrans->GetForward(); // �O�����������x�N�g��
        // �R���W����������
        auto ptrColl = AddComponent<CollisionObb>();
        // �Փ˔����Auto
        ptrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"PlayerBullet");
    
        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_Transform = GetComponent<Transform>();
        m_Transform->SetPosition(ownerTrans->GetPosition() + m_forward * 0.75f); // �I�[�i�[�Əd�Ȃ�Ȃ��悤�ɁA�i�s�����ɏ������炷
        m_Transform->SetQuaternion(ownerTrans->GetQuaternion());
        m_Transform->SetScale(Vec3(0.5f));

    }

    void PlayerBullet::OnUpdate()
    {
        auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����Ȃ��Ƃ�
        if (levelUpEvent->GetEventActive() || !player->GetDrawActive())
        {
            // �������~����
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_Transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_Transform->SetPosition(pos);
        
        // �e�������ɍs���������
        if (pos.length() > 50.0f)
        {
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
        }
    }

    void PlayerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
    {
        // �G�ɂ���������
        if (other->FindTag(L"Enemy"))
        {
            // ����
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
            return;
        }
    }

}
