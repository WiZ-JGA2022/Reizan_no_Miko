/*!
@file PlayerController.cpp
@brief �v���C���[�L����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void PlayerController::OnCreate() // Unity��Start���\�b�h(�֐�)�̂悤�Ȃ���
	{
		// Player�I�u�W�F�N�g�̏����ݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, 0.0f, 0.0f);
	}

	void PlayerController::OnUpdate()
	{
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


		// �J�����ɉ�荞�݂̎擾
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += padLStick * 3.0f * delta;

		transComp->SetPosition(pos);

		if (padLStick.length() > 0.0f) // �X�e�B�b�N�̓��͊m�F
		{
			// �X�e�B�b�N�̌X���ɍ��킹�ăI�u�W�F�N�g����]������
			float rotY = atan2f(-padLStick.z, padLStick.x); // 2�����x�N�g�����p�x(���W�A��)�ɕϊ�����
			transComp->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // Y�����S�̉�]�i�L�����N�^�[���[���x�����Ɍ������邽�߂�90�x������]������j
		}
	}
	void PlayerController::OnPushX() {
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		pos.y += 0.3f;
		Quat qt = ptrTrans->GetQuaternion();
		Vec3 rot = qt.toRotVec();
		float rotY = rot.y;
		Vec3 velo(sin(rotY), 0.1f, cos(rotY));
		velo.normalize();
		velo *= 15.0f;
		auto group = GetStage()->GetSharedObjectGroup(L"FireSphereGroup");
		auto& vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				if (!shObj->IsUpdateActive()) {
					auto shFire = dynamic_pointer_cast<FireSphere>(shObj);
					if (shFire) {
						shFire->Reset(pos, velo);
						return;
					}
				}
			}
		}
		//�󂪂Ȃ������̂ŐV���ɍ쐬
		GetStage()->AddGameObject<FireSphere>(pos, velo);
	}

	//void OnCollisionEnter(const CollisionPair& Pair)
	//{
	//	// ���x���A�b�v�C�x���g���͏������~����
	//	//if (levelUpEvent.GetComponent<LevelUpEvent>().GetActiveOrUnActive())
	//	//{
	//	//	return;
	//	//}
	//	//if (collision.gameObject.tag == "EnemyBullet")
	//	//{
	//	//	getStatus.GetComponent<PlayerStatusController>().PlayerTakenDamage();
	//	//}

	//}

	//void 
	//{
	//	// ���x���A�b�v�C�x���g���͏������~����
	//	//if (levelUpEvent.GetComponent<LevelUpEvent>().GetActiveOrUnActive())
	//	//{
	//	//	return;
	//	//}
	//	//// �G�Ɠ���������
	//	//if ()
	//	//{
	//	//	// ������HP�������Ă���
	//	// 
	//	//}

	//}

	void PlayerSpeedUp(float level)
	{

	}

	void PlayerController::DestroyPlayer()
	{
		
	}
}
