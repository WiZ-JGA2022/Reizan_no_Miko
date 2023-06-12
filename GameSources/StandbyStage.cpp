/*!
@file StandbyStage.cpp
@brief �����t�F�[�Y�X�e�[�W�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StandbyStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}


	//�v���C���[�̍쐬
	void StandbyStage::CreatePlayer() {
		auto player = AddGameObject<PlayerController>(0);
		SetSharedGameObject(L"Player", player);
		player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_RED");
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_GREEN");
	} // end CreatePlayer	

	void StandbyStage::CreateUI()
	{
		// Hp�o�[�̍쐬
		AddGameObject<HpBar>();

		// Hp�̐����\�L���쐬
		AddGameObject<HpNumber>();

		AddGameObject<StrengthSprite>();

		// �c�莞�Ԃ̕\��UI���쐬
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false,true);
		SetSharedGameObject(L"Time", time);

		AddGameObject<TimeChara>();

		AddGameObject<TrapSelect>();

		AddGameObject<ButtonSelect>();

		AddGameObject<StandbySprite>();

		AddGameObject<TrapNumber>();

		AddGameObject<TutorialUI>();

		AddGameObject<RBButtonSprite>();
		AddGameObject<HoldBar>();
	} // end CreateUI


	void StandbyStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_bgm = XAPtr->Start(L"STANDBY_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void StandbyStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void StandbyStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[���[�̍쐬
			CreatePlayer();

			// �n�ʂ̍쐬
			AddGameObject<Field>();
			AddGameObject<StageCollision>(Vec3(30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -16.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-16.0f, 1.0f, 7.5f), Vec3(28.0f, 3.0f, 8.5f));
			AddGameObject<StageCollision>(Vec3(14.5f, 1.0f, 26.0f), Vec3(31.5f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(7.5f, 1.0f, 53.0f), Vec3(3.0f, 3.0f, 18.0f));
			AddGameObject<StageCollision>(Vec3(-8.0f, 1.0f, 52.0f), Vec3(3.0f, 3.0f, 16.5f));

			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);

			// UI�̍쐬
			CreateUI();
			AddGameObject<FadeIn>(L"FADE_WHITE");
			PlayBGM();

			// ���C���J�����Ƀv���C���[���Z�b�g����
			auto player = GetSharedGameObject<PlayerController>(L"Player");
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
			maincamera->SetTargetObject(player);
		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {

		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		// ���Z�b�g�R�}���h
		if (pad.wButtons & XINPUT_GAMEPAD_START && pad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			m_isChangeStage = true;
			// �^�C�g���ɖ߂�
			PostEvent(0.1f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
		}

		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		if (time->GetTimeLeft() <= 0.0f)
		{
			ChangeStage();
		}
	}

	// �f�o�b�O������\���p
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	void StandbyStage::ChangeStage()
	{
		m_isChangeStage = true;

		// �e������V�[���ɐݒ�
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto camera = GetView()->GetTargetCamera();
		auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
		scene->SetBeforePlayerPosition(player->GetComponent<Transform>()->GetPosition());
		scene->SetBeforePlayerQuaternion(player->GetComponent<Transform>()->GetQuaternion());
		scene->SetBeforeCameraRadXZ(maincamera->GetRadXZ());
		scene->SetBeforeCameraRadY(maincamera->GetRadY());
		scene->SetBeforeCameraAngle(maincamera->GetAngle());
		scene->SetBeforeCameraAt(maincamera->GetAt());

		// �Q�[���X�e�[�W�ֈړ�
		PostEvent(0.01f, GetThis<ObjectInterface>(), scene, L"ToFirstStage");
	}
}