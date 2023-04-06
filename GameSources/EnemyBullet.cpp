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
        
        // �����̃g�����X�t�H�[���R���|�[�l���g���擾���č��W��傫����ݒ肷��
        m_transform = GetComponent<Transform>();
        m_transform->SetPosition(ownerTrans->GetPosition());
        m_transform->SetScale(Vec3(0.5f));


        MoveEnemyBullet();

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

        m_position += m_direction * m_speed * delta;// �ړ��̌v�Z

        m_transform->SetPosition(m_position); // �ړ�����
    }

    Vec3 EnemyBullet::MoveEnemyBullet()
    {
        // �f���^�^�C���̎擾
        auto& app = App::GetApp();
        float delta = app->GetElapsedTime();

        // �e��x�N�g���̎擾
        auto pos = m_transform->GetPosition(); // ���g�̈ʒu�x�N�g�����擾
        auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
        auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

        m_direction = playerPos - pos; // �v���C���[�ւ̕������v�Z

        // �x�N�g���̐��K������
        float normalizeMagnification = 1 / sqrt(
            m_direction.x * m_direction.x +
            m_direction.y * m_direction.y +
            m_direction.z * m_direction.z);
        m_direction *= normalizeMagnification;
        // �����܂�

        //pos += m_direction * m_speed * delta;	// �ړ��̌v�Z
        float rotationY = atan2f(-(playerPos.z - pos.z), playerPos.x - pos.x); // ��]�̌v�Z

        //m_transform->SetPosition(pos); // �ړ�����
        m_transform->SetRotation(Vec3(0, rotationY, 0)); // ��]����

        return m_direction;
    }

}
//end basecross
