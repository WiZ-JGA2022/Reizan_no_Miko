/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f, 1.0f ,0.0f);

		auto PtrView = CreateView<SingleView>();
		
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

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
		m_player = AddGameObject<PlayerController>(0);
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
		m_time = AddGameObject<TimeNumber>(20.0f, false);
		SetSharedGameObject(L"Time", m_time);
		
		AddGameObject<TimeChara>();

		AddGameObject<TrapSelect>();

		m_standby = AddGameObject<StandbySprite>();

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
			AddGameObject<Field2>(Vec3(10.0f, 3.5f, 10.0f));
			AddGameObject<Field2>(Vec3(-10.0f, 3.5f, 30.0f));
			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);

			// �M�~�b�N�̍쐬
			//auto gimmick = AddGameObject<TrapController>();
			//SetSharedGameObject(L"TrapController", gimmick);

			// UI�̍쐬
			CreateUI();
			PlayBGM();

			// ���C���J�����Ƀv���C���[���Z�b�g����
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			maincamera->SetTarget(m_player);
		}
		catch (...) {
			throw;
		}
	}

	//�X�V
	void GameStage::OnUpdate() {
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		if (time->GetTimeLeft() <= 0.0f)
		{
			player->SetCondition(1);
			RemoveGameObject<TimeNumber>(m_time);
			RemoveGameObject<StandbySprite>(m_standby);
			if (m_isOnce)
			{
				AddGameObject<TimeNumber>(60.0f, true);
				AddGameObject<GameSprite>();
				m_isOnce = false;
				return;
			}
		}
		if (!player->GetDrawActive())
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			return;
		}
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
		PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

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
