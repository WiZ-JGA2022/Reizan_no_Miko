/*!
@file PlayerController.cpp
@brief �v���C���[�L����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class PlayerController : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	PlayerController::PlayerController(const std::shared_ptr<Stage>& stage, const int condition) :
		GameObject(stage),
		m_RecastCount(9.0f),
		m_spikeTrapCount(0),
		m_lavaTrapCount(0),
		m_position(Vec3(0)),
		m_quaternion(Quat(0)),
		m_condition((PlayerCondition)condition),
		m_recastFlame(m_RecastCount)
	{
	}
	PlayerController::PlayerController(const std::shared_ptr<Stage>& stage, const Vec3& position, const Quat& quaternion, const int condition) :
		GameObject(stage),
		m_RecastCount(9.0f),
		m_spikeTrapCount(0),
		m_lavaTrapCount(0),
		m_position(position),
		m_quaternion(quaternion),
		m_condition((PlayerCondition)condition),
		m_recastFlame(m_RecastCount)
	{
	}
	PlayerController::~PlayerController() {}


	void PlayerController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position.x, 0.4f, m_position.z);
		m_transform->SetQuaternion(m_quaternion);
		m_transform->SetScale(1.0f, 1.0f, 1.0f);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		// �Փ˔����Auto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
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
		ptrShadow->SetMeshResource(L"MIKO_WALK");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g�̐ݒ�
		auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		drawComp->SetFogEnabled(false);
		//�`�悷�郁�b�V����ݒ�
		drawComp->SetMeshResource(L"MIKO_WALK");
		drawComp->SetMeshToTransformMatrix(spanMat);
		drawComp->AddAnimation(L"walk_player", 0, 30, true, 20.0f);
		drawComp->ChangeCurrentAnimation(L"walk_player");

		//��������
		SetAlphaActive(true);

		SetDrawActive((int)DrawLayer::Bottom);
	}

	void PlayerController::OnUpdate()
	{
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		if (playerStatus->GetStatusValue(L"HP") <= 0)
		{
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

		m_recastFlame -= 0.1f;
		
		PlayerMoveProcess();

		if (m_recastFlame <= 0 && m_condition == PlayerCondition::Play)
		{
			GetStage()->AddGameObject<PlayerBullet>(GetThis<PlayerController>());

			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}

		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		// �v���C���[�̏�Ԃ�������ԂȂ�
		if (m_condition == PlayerCondition::Standby)
		{	
			// �X�p�C�N�g���b�v�̏�������Ȃ�
			if (m_trapCount[0] < (int)TrapLimit::SpikeTrap)
			{
				if (pad.wPressedButtons & XINPUT_GAMEPAD_X)
				{
					auto XAPtr = app->GetXAudio2Manager();
					XAPtr->Start(L"SPIKE_SE", 0, 0.3f);

					Vec3 trapPosition = Vec3(m_transform->GetPosition().x, -0.5f, m_transform->GetPosition().z);
					GetStage()->AddGameObject<SpikeTrap>(trapPosition, Vec3(5.0f, 0.5f, 5.0f));
					app->GetScene<Scene>()->SetBeforeSpikePosition(trapPosition, m_trapCount[0]);
					m_trapCount[0]++;
				}
			}
			// �n��㩂̏�������Ȃ�
			if (m_trapCount[1] < (int)TrapLimit::SpurtLava)
			{
				if (pad.wPressedButtons & XINPUT_GAMEPAD_Y)
				{
					auto XAPtr = app->GetXAudio2Manager();
					XAPtr->Start(L"SPIKE_SE", 0, 0.3f);

					Vec3 trapPosition = Vec3(m_transform->GetPosition().x, -0.5f, m_transform->GetPosition().z);
					GetStage()->AddGameObject<SpurtLava>(trapPosition, Vec3(4.0f, 20.0f, 4.0f));
					app->GetScene<Scene>()->SetBeforeLavaPosition(trapPosition, m_trapCount[1]);
					m_trapCount[1]++;
				}
			}
		}
	}

	void PlayerController::PlayerMoveProcess()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		if (padLStick.length() > 0.0f)
		{
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			//XAPtr->Start(L"PLAYERRUN_SE", 1, 0.1f);

			float stickRad = atan2(padLStick.z, padLStick.x);
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MyCamera>(camera);
			if (mainCamera)
			{
				float cameraAngle = mainCamera->GetAngle();

				stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}

			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

			// �ړ�����
			auto pos = m_transform->GetPosition();
			pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;

			m_transform->SetPosition(pos);
			float rotY = atan2f(-padLStick.z, padLStick.x);
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // ��]����
		}
	}
}
