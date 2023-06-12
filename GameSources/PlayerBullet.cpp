/*!
@file PlayerBullet.cpp
@brief �v���C���[�����˂���e
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

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
        auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
        m_forward = playerTrans->GetForward(); // �O�����������x�N�g��
        // �R���W����������
        auto ptrColl = AddComponent<CollisionObb>();
        // �Փ˔����Auto
        ptrColl->SetAfterCollision(AfterCollision::None);

        // �^�O�̒ǉ�
        AddTag(L"PlayerBullet");
    
        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(playerTrans->GetPosition() + m_forward * 0.75f); // �I�[�i�[�Əd�Ȃ�Ȃ��悤�ɁA�i�s�����ɏ������炷
        m_transform->SetQuaternion(playerTrans->GetQuaternion());
        m_transform->SetScale(Vec3(0.5f));

    }

    void PlayerBullet::OnUpdate()
    {
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����Ȃ��Ƃ�
        if (!player->GetDrawActive())
        {
            // �������~����
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        auto pos = m_transform->GetPosition();
        pos += m_forward * m_speed * delta;
        m_transform->SetPosition(pos);
        
        // �e�������ɍs���������
        if (pos.length() > 70.0f)
        {
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
        }
    }

    void PlayerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
    {
        // �G�܂��̓X�e�[�W�ɂ���������
        if (other->FindTag(L"Enemy") || other->FindTag(L"Stage"))
        {
            // ����
            GetStage()->RemoveGameObject<PlayerBullet>(GetThis<PlayerBullet>());
            return;
        }
    }

}
