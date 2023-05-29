/*!
@file EnemyBullet.cpp
@brief �G�̒e�@����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    void EnemyBullet::OnCreate()
    {
        auto ptrColl = AddComponent<CollisionSphere>();
        // �Փ˔����None
        ptrColl->SetAfterCollision(AfterCollision::None);

        auto drawComp = AddComponent<PNTStaticDraw>();
        drawComp->SetMeshResource(L"DEFAULT_SPHERE");
        drawComp->SetEmissive(Col4(0.4f, 0.6f, 0.9f, 1.0f));

        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(m_position);
        m_transform->SetScale(m_scale);

        MoveEnemyBullet();
    }

    void EnemyBullet::OnUpdate()
    {
        auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
        // �v���C���[�����Ȃ�������
        if (!player->GetDrawActive())
        {
            // �������~����
            return;
        }

        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        m_position += m_direction * m_speed * delta; // �ړ��̌v�Z

        m_transform->SetPosition(m_position); // �ړ�����

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
        // �f���^�^�C���̎擾
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        // �x�N�g���̎擾
        auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
        auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu���擾

        m_direction = playerPos - m_position; // �v���C���[�Ƃ̋������v�Z

        // �x�N�g���̐��K������
        float normalizeMagnification = 1 / sqrt(
            m_direction.x * m_direction.x +
            m_direction.y * m_direction.y +
            m_direction.z * m_direction.z);
        m_direction *= normalizeMagnification;
        // �����܂�w

        float rotationY = atan2f(-m_direction.z, m_direction.x); // ��]�̌v�Z
        m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����
    }
}
//end basecross
