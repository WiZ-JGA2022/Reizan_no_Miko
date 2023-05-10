/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StandbyStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, 10.0f);
		const Vec3 at(0.0f, 1.0f, 0.0f);

		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

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

			

			auto blockingStone = AddGameObject<BlockingStone>();
			SetSharedGameObject(L"BlockingStone", blockingStone);

			// UI�̍쐬
			CreateUI();
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
			scene->SetBeforeCameraEye(maincamera->GetEye());
			scene->SetBeforeCameraAt(maincamera->GetAt());
			scene->SetBeforeCameraArmVec(maincamera->GetArmVec());
			scene->SetBeforeCameraArmLength(maincamera->GetArmLengh());
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");
		}

		wstringstream wss;
		wss << L"CurrentEye : " <<
			maincamera->GetEye().x << L" " <<
			maincamera->GetEye().y << L" " <<
			maincamera->GetEye().z << L"\n" <<
			L"CurrentAt : " <<
			maincamera->GetAt().x << L" " <<
			maincamera->GetAt().y << L" " <<
			maincamera->GetAt().z << L"\n" <<
			L"CurrentArmVec : " <<
			maincamera->GetArmVec().x << L" " <<
			maincamera->GetArmVec().y << L" " <<
			maincamera->GetArmVec().z << L"\n" <<
			L"CurrentArmLength : " <<
			maincamera->GetArmLengh() << endl;
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());


	}

	// �f�o�b�O������\���p
	void StandbyStage::OnDraw()
	{
		Stage::OnDraw(); 
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		
		auto scene = App::GetApp()->GetScene<Scene>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		auto beforeEye = scene->GetBeforeCameraEye();
		PtrCamera->SetAt(scene->GetBeforeCameraAt());
		PtrCamera->SetEye(beforeEye);
		auto eye = PtrCamera->GetEye();
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	// �G�̍쐬
	void GameStage::CreateEnemy() {
		CreateSharedObjectGroup(L"EnemyGroup");
		auto enemyController = AddGameObject<EnemyController>();
		SetSharedGameObject(L"EnemyController", enemyController);
	}

	// ���x���A�b�v�C�x���g�̍쐬
	void GameStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		Vec3 beforePlayerPosition = App::GetApp()->GetScene<Scene>()->GetBeforePlayerPosition();
		Quat beforePlayerQuaternion = App::GetApp()->GetScene<Scene>()->GetBeforePlayerQuaternion();
		m_player = AddGameObject<PlayerController>(beforePlayerPosition, beforePlayerQuaternion, 1);
		SetSharedGameObject(L"Player", m_player);
		m_player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
	} // end CreatePlayer	

	void GameStage::CreateUI()
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

		AddGameObject<GameSprite>();
	} // end CreateUI

	void GameStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void GameStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[���[�̍쐬
			CreatePlayer();
			// �G�̍쐬
			CreateEnemy();
			// ���x���A�b�v�C�x���g�̍쐬
			CreateLevelUpEvent();

			// �n�ʂ̍쐬
			AddGameObject<Field>();
			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);
			AddGameObject<StageCollision>(Vec3(29.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision2>(Vec3(-30.4f, 4.5f, 30.0f));
			AddGameObject<StageCollision3>(Vec3(0.0f, 4.5f, -15.0f));
			AddGameObject<StageCollision4>(Vec3(-17.5f, 1.0f, 12.5f));
			AddGameObject<StageCollision5>(Vec3(13.5f, 1.0f, 28.0f));
			AddGameObject<StageCollision6>(Vec3(13.0f, 1.0f, 58.0f));
			AddGameObject<StageCollision7>(Vec3(-13.5f, 1.0f, 57.5f));

			AddGameObject<KeyStoneGauge>(stone);

			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			for (int i = 0; i < scene->GetBeforePlacedTrap(0); i++)
			{
				AddGameObject<SpikeTrap>(scene->GetBeforeSpikePosition(i), Vec3(5.0f, 0.5f, 5.0f));
			}
			for (int i = 0; i < scene->GetBeforePlacedTrap(1); i++)
			{
				AddGameObject<SpurtLava>(scene->GetBeforeLavaPosition(i), Vec3(4.0f, 20.0f, 4.0f));
			}

			// UI�̍쐬
			CreateUI();
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

	//�X�V
	void GameStage::OnUpdate() {
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		if (!player->GetDrawActive())
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			return;
		}

		auto scene = App::GetApp()->GetScene<Scene>();
		auto camera = GetView()->GetTargetCamera();
		auto maincamera = dynamic_pointer_cast<MyCamera>(camera);
		wstringstream wss;
		wss << L"BeforeEye : " <<
			scene->GetBeforeCameraEye().x << L" " <<
			scene->GetBeforeCameraEye().y << L" " <<
			scene->GetBeforeCameraEye().z << L"\n" <<
			L"CurrentEye : " <<
			maincamera->GetEye().x << L" " <<
			maincamera->GetEye().y << L" " <<
			maincamera->GetEye().z << L"\n" <<

			L"BeforeAt : " <<
			scene->GetBeforeCameraAt().x << L" " <<
			scene->GetBeforeCameraAt().y << L" " <<
			scene->GetBeforeCameraAt().z << L"\n" <<
			L"CurrentAt : " <<
			maincamera->GetAt().x << L" " <<
			maincamera->GetAt().y << L" " <<
			maincamera->GetAt().z << L"\n" <<

			L"BeforeArmVec : " <<
			scene->GetBeforeCameraArmVec().x << L" " <<
			scene->GetBeforeCameraArmVec().y << L" " <<
			scene->GetBeforeCameraArmVec().z << L"\n" <<
			L"CurrentArmVec : " <<
			maincamera->GetArmVec().x << L" " <<
			maincamera->GetArmVec().y << L" " <<
			maincamera->GetArmVec().z << L"\n" <<

			L"BeforeArmLength : " <<
			scene->GetBeforeCameraArmLength() << L"\n" <<
			L"CurrentArmLength : " <<
			maincamera->GetArmLengh() << endl;
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());
	} // end OnUpdate

	void GameStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//�X�v���C�g�̍쐬
	void TitleStage::CreateTitleSprite() {
		AddGameObject<TitleSprite>();
		AddGameObject<StartSprite>();
	} // end CreateTitleSprite

	void TitleStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void TitleStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//������
	void TitleStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();

		PlayBGM();

	} // end OnCreate

	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());

	} // end OnUpdate

	//B�{�^��
	void TitleStage::OnPushB() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"SELECT_SE", 0, 0.5f);
		PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");

	} // end OnPushB


	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//�X�v���C�g�̍쐬
	void ResultStage::CreateResultSprite() {
		AddGameObject<ResultSprite>();
	} // end CreateResultSprite

	void ResultStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GAMEOVER_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void ResultStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//������
	void ResultStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateResultSprite();
		PlayBGM();
	} // end OnCreate

	//�X�V
	void ResultStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<ResultStage>());

	} // end OnUpdate

	//B�{�^��
	void ResultStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB

	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//�X�v���C�g�̍쐬
	void ClearStage::CreateResultSprite() {
		AddGameObject<ClearSprite>();
	} // end CreateResultSprite

	void ClearStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GAMECLEAR_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void ClearStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//������
	void ClearStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateResultSprite();
		PlayBGM();
	} // end OnCreate

	//�X�V
	void ClearStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<ClearStage>());

	} // end OnUpdate

	//B�{�^��
	void ClearStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB

}
//end basecross
