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
		m_transform->SetScale(Vec3(1.0f, 1.0f, 1.0f));
		m_transform->SetRotation(Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f));
		m_transform->SetPosition(m_position);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

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
		ptrShadow->SetMeshResource(L"SPURTLAVA_MODEL");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		// �����ڂ̐ݒ�
		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"SPURTLAVA_MODEL");
		drawComp->SetMeshToTransformMatrix(spanMat);

		// �^�O�̒ǉ�
		AddTag(L"SpurtLava");
		// ����������L����
		SetAlphaActive(true);
		// �`�惌�C���[��ݒ�
		SetDrawLayer((int)DrawLayer::Bottom);

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"Lava.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
	}

	void SpurtLava::OnUpdate()
	{
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
			
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		// ��{�I�ɃR���W������ҋ@��Ԃɂ��Ă���
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetUpdateActive(false);

		// �v���C���[���`�悳��Ȃ��Ȃ�����
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (!player->GetDrawActive())
		{
			// �G�t�F�N�g��SE���~����
			if (m_isState == TrapState::Active)
			{
				m_EfkPlay->StopEffect();
			}
			XAPtr->Stop(m_se[0]);
			XAPtr->Stop(m_se[1]);
		}

		// �v���C���[�̏�Ԃ��X�^���o�C��ԂłȂ��Ƃ�
		if (player->GetCondition() != 0)
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& firstStage = dynamic_pointer_cast<FirstStage>(stage);
			// �X�e�[�W���؂�ւ������
			if (firstStage->GetChangingStage())
			{
				// �G�t�F�N�g��SE���~����
				if (m_isState == TrapState::Active)
				{
					m_EfkPlay->StopEffect();
				}
				XAPtr->Stop(m_se[0]);
				XAPtr->Stop(m_se[1]);
			}

			if (m_isState == TrapState::Wait)
			{
				// R�X�e�B�b�N���������񂾂�
				if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				{
					// SE�̍Đ�
					m_se[0] = XAPtr->Start(L"LAVA_SE", 0, 0.3f);
					// ���s�ҋ@��Ԃɓ���
					m_isState = TrapState::ActiveDelay;
				}
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
				// �R���W�������擾�����傫���ɕύX
				ptrColl->SetMakedSize(3);
				// SE�̍Đ�
				m_se[1] = XAPtr->Start(L"SPURTLAVA_SE", 0, 0.3f);
				// ���s��Ԃɓ���
				m_isState = TrapState::Active;
				// �ҋ@���Ԃ����������Ă���
				m_activeFlame = m_DamageActiveDelayFlame;

				//�G�t�F�N�g�̃v���C
				m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, m_transform->GetPosition(), Vec3(0.5f));
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
			}
			// �폜�܂ł̎��Ԃ�0�ɂȂ�����
			if (m_removeDelayFlame <= 0)
			{
				XAPtr->Stop(m_se[0]);
				XAPtr->Stop(m_se[1]);
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

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		// �Փ˔����None
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(false);

		AddTag(L"SpikeTrap");

		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::Bottom);

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"E_aura.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//�G�t�F�N�g�̃v���C
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, m_transform->GetPosition(), Vec3(1.0f));
	}

	void SpikeTrap::OnUpdate()
	{
		// �e��I�u�W�F�N�g�̏����擾
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetStage()->GetSharedGameObject<TimeNumber>(L"Time");
		auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");

		// �v���C���[���X�^���o�C��Ԃ���Ȃ��Ƃ�
		if (player->GetCondition() != 0)
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& firstStage = dynamic_pointer_cast<FirstStage>(stage);
			// �X�e�[�W���ς������
			if (firstStage->GetChangingStage())
			{
				// �G�t�F�N�g������
				m_EfkPlay->StopEffect();
			}
		}
		else
		{
			auto& stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto& standbyStage = dynamic_pointer_cast<StandbyStage>(stage);
			if (standbyStage->GetChangingStage())
			{
				// �G�t�F�N�g������
				m_EfkPlay->StopEffect();
			}
		}

		// �u�v���C���[��������v�u���Ԑ؂�ɂȂ�v�u�΂�����v�̂����ǂꂩ�𖞂�������
		if (!player->GetDrawActive() || time->GetTimeLeft() < 0.0f || stone->GetCurrentHp() < 0.0f)
		{
			// �G�t�F�N�g������
			m_EfkPlay->StopEffect();
		}
	}

	void SpikeTrap::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// enemy�ɓ���������
		if (other->FindTag(L"Enemy"))
		{
			// ���I�u�W�F�N�g��ǉ����A���̃I�u�W�F�N�g������
			GetStage()->AddGameObject<SpikeModel>(m_transform->GetPosition());
			GetStage()->RemoveGameObject<SpikeTrap>(GetThis<SpikeTrap>());
		}
	}
}