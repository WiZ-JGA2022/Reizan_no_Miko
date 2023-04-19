/*!
@file TrapGroup.cpp
@brief 㩂̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpurtLava::SpurtLava(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_activeFlame(m_DamageActiveDelayFlame),
		m_removeDelayFlame(m_RemoveDelayCount),
		m_scale(scale),
		m_position(position)
	{
	}
	SpurtLava::~SpurtLava() {}

	void SpurtLava::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpurtLava");
	}

	void SpurtLava::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
			
		// ��{�I�ɃR���W������ҋ@��Ԃɂ��Ă���
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		ptrColl->SetDrawActive(false);

		// �v���C���[�̏�Ԃ����s��Ԃ̂Ƃ�R�X�e�B�b�N���������񂾂�
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (player->GetCondition() == 1)
		{
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				// ���s�ҋ@��Ԃɓ���
				m_isState = TrapState::ActiveDelay;
			}
		}

		// ���s�ҋ@��ԂȂ�
		if (m_isState == TrapState::ActiveDelay)
		{
			// �ҋ@���Ԃ�����
			m_activeFlame--;
			// �ҋ@���Ԃ��I�������
			if (m_activeFlame <= 0)
			{
				// ���s��Ԃɓ���
				m_isState = TrapState::Active;
				// �ҋ@���Ԃ����������Ă���
				m_activeFlame = m_DamageActiveDelayFlame;
			}
		}

		// ���s��ԂȂ�
		if (m_isState == TrapState::Active)
		{
			// �폜�܂ł̎��Ԃ��o�߂�����
			m_removeDelayFlame--;

			// �_���[�W��^����Ԋu���ɃR���W�������A�N�e�B�u�ɂ���
			if (m_removeDelayFlame % m_DamageIntervalFlame == 0)
			{
				ptrColl->SetUpdateActive(true);
				ptrColl->SetDrawActive(true);
			}
			// �폜�܂ł̎��Ԃ�0�ɂȂ�����
			if (m_removeDelayFlame <= 0)
			{
				// �ҋ@��ԂɈڍs
				m_isState = TrapState::Wait;
				// ���̃I�u�W�F�N�g�̍폜
				GetStage()->RemoveGameObject<SpurtLava>(GetThis<SpurtLava>());
			}
		}
	}


	SpikeTrap::SpikeTrap(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale) :
		GameObject(stage),
		m_scale(scale),
		m_position(position)
	{
	}
	SpikeTrap::~SpikeTrap() {}

	void SpikeTrap::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetScale(m_scale);
		m_transform->SetPosition(m_position);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SPIKE");

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpikeTrap");

		SetAlphaActive(true);
	}

	void SpikeTrap::OnUpdate()
	{
	}

	void SpikeTrap::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Enemy"))
		{
			GetStage()->RemoveGameObject<SpikeTrap>(GetThis<SpikeTrap>());
		}
	}
}