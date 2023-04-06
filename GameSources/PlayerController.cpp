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
	//�\�z�Ɣj��

	void PlayerController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(0.0f, 0.0f, 0.0f);

		// �R���W����������
		auto ptrColl = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(false);

		// �e������
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		// Player�I�u�W�F�N�g�̏����ݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
	}

	void PlayerController::OnUpdate()
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		levelUpEvent->LevelUpEvent();
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		if (playerStatus->GetStatusValue(L"HP") <= 0)
		{
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		
		m_recastFlame -= 0.1f;

		// Player�̈ړ�����
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime(); // �O�t���[������̌o�ߎ��ԁi60FPS�j

		// �Q�[���p�b�h���g�p����
		auto device = app->GetInputDevice(); // �C���v�b�g�f�o�C�X�I�u�W�F�N�g���擾����
		auto& pad = device.GetControlerVec()[0]; // �P�ڂ̃R���g���[���[�̏�Ԃ��擾����

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		if (padLStick.length() > 0.0f)
		{
			float stickRad = atan2(padLStick.z, padLStick.x);

			// �J�����̉�荞�݂��擾
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
			if (mainCamera)
			{
				float cameraAngle = mainCamera->GetAngle();

				stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}
		}

		// �ړ�����
		auto pos = m_transform->GetPosition();
		pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;

		m_transform->SetPosition(pos);

		if (padLStick.length() > 0.0f) // �X�e�B�b�N�̓��͊m�F
		{
			// �X�e�B�b�N�̌X���ɍ��킹�ăI�u�W�F�N�g����]������
			float rotY = atan2f(-padLStick.z, padLStick.x); // 2�����x�N�g�����p�x(���W�A��)�ɕϊ�����
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // Y�����S�̉�]�i�L�����N�^�[���[���x�����Ɍ������邽�߂�90�x������]������j
		}

		if (m_recastFlame <= 0)
		{
			GetStage()->AddGameObject<PlayerBullet>(GetThis<PlayerController>());
			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}
	}

	void PlayerController::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto levelUpEvent = GetStage()->GetSharedGameObject<RandomSelectLevelUpButton>(L"LevelUpEvent");
		if (levelUpEvent->GetControllerSprite())
		{
			return;
		}

		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		if (other->FindTag(L"Enemy"))
		{
			playerStatus->PlayerDamageProcess();
			return;
		}

	}
}
