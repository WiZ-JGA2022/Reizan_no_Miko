/*!
@file StandbyStage.cpp
@brief �����t�F�[�Y�X�e�[�W�̎���
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

	// ���x���A�b�v�C�x���g�̍쐬
	void StandbyStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//�v���C���[�̍쐬
	void StandbyStage::CreatePlayer() {
		m_player = AddGameObject<PlayerController>(0);
		SetSharedGameObject(L"Player", m_player);
		m_player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
	} // end CreatePlayer	

	void StandbyStage::CreateUI()
	{
		// Exp�o�[��Hp�o�[�̍쐬
		AddGameObject<HpBar>();
		AddGameObject<ExpBar>();

		// Hp��Exp�̐����\�L���쐬
		AddGameObject<HpNumber>();
		AddGameObject<ExpNumber>();

		// �c�莞�Ԃ̕\��UI���쐬
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false);
		SetSharedGameObject(L"Time", time);

		AddGameObject<TimeChara>();

		AddGameObject<TrapSelect>();

		AddGameObject<ButtonSelect>();

		AddGameObject<StandbySprite>();

		AddGameObject<TrapNumber>();

		AddGameObject<TutorialUI>();
	} // end CreateUI


	void StandbyStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void StandbyStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void StandbyStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			CreateLevelUpEvent();
			//�v���[���[�̍쐬
			CreatePlayer();

			// �n�ʂ̍쐬
			AddGameObject<Field>();
			AddGameObject<StageCollision>(Vec3(29.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision2>(Vec3(-30.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision3>(Vec3(0.0f, 4.5f, -15.0f));
			AddGameObject<StageCollision4>(Vec3(-17.5f, 1.0f, 12.5f));
			AddGameObject<StageCollision5>(Vec3(13.5f, 1.0f, 28.0f));
			AddGameObject<StageCollision6>(Vec3(13.0f, 1.0f, 58.0f));
			AddGameObject<StageCollision7>(Vec3(-13.5f, 1.0f, 57.5f));

			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);

			AddGameObject<KeyStoneGauge>(stone);

			// UI�̍쐬
			CreateUI();
			AddGameObject<FadeIn>();
			PlayBGM();

			// ���C���J�����Ƀv���C���[���Z�b�g����
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
			maincamera->SetTargetObject(m_player);
		}
		catch (...) {
			throw;
		}
	}

	void StandbyStage::OnUpdate() {
		auto scene = App::GetApp()->GetScene<Scene>();
		auto camera = GetView()->GetTargetCamera();
		auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		if (time->GetTimeLeft() <= 0.0f)
		{
			scene->SetBeforePlayerPosition(m_player->GetComponent<Transform>()->GetPosition());
			scene->SetBeforePlayerQuaternion(m_player->GetComponent<Transform>()->GetQuaternion());
			scene->SetBeforeCameraRadXZ(maincamera->GetRadXZ());
			scene->SetBeforeCameraRadY(maincamera->GetRadY());
			scene->SetBeforeCameraAngle(maincamera->GetAngle());
			scene->SetBeforeCameraAt(maincamera->GetAt());
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToFirstStage");
		}
	}

	// �f�o�b�O������\���p
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

}