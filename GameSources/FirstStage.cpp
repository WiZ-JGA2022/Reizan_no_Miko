/*!
@file FirstStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void FirstStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		
		auto scene = App::GetApp()->GetScene<Scene>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetAt(scene->GetBeforeCameraAt());
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	// �G�̍쐬
	void FirstStage::CreateEnemy() {
		CreateSharedObjectGroup(L"EnemyGroup");
		auto enemyController = AddGameObject<EnemyController>();
		SetSharedGameObject(L"EnemyController", enemyController);
	}

	// ���x���A�b�v�C�x���g�̍쐬
	void FirstStage::CreateLevelUpEvent() {
		auto levelUpEvent = AddGameObject<RandomSelectLevelUpButton>();

		SetSharedGameObject(L"LevelUpEvent", levelUpEvent);
	}

	//�v���C���[�̍쐬
	void FirstStage::CreatePlayer() {
		Vec3 beforePlayerPosition = App::GetApp()->GetScene<Scene>()->GetBeforePlayerPosition();
		Quat beforePlayerQuaternion = App::GetApp()->GetScene<Scene>()->GetBeforePlayerQuaternion();
		m_player = AddGameObject<PlayerController>(beforePlayerPosition, beforePlayerQuaternion, 1);
		SetSharedGameObject(L"Player", m_player);
		m_player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
	} // end CreatePlayer	

	void FirstStage::CreateUI()
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

	void FirstStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void FirstStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void FirstStage::OnCreate() {
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
			AddGameObject<StageCollision>(Vec3(29.4f, 4.5f, 30.0f), Vec3(1.0f, 1.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 30.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -15.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-17.5f, 1.0f, 12.5f), Vec3(28.0f, 3.0f, 7.5f));
			AddGameObject<StageCollision>(Vec3(13.5f, 1.0f, 28.0f), Vec3(31.0f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(13.0f, 1.0f, 58.0f), Vec3(5.0f, 3.0f, 16.0f));
			AddGameObject<StageCollision>(Vec3(-13.5f, 1.0f, 57.5f), Vec3(5.0f, 3.0f, 14.5f));
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

			AddGameObject<EffectController>()->OnDraw();
			AddGameObject<EffectController>()->OnDraw2();
			AddGameObject<EffectController>()->OnDraw3();
			AddGameObject<EffectController>()->OnDraw4();

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
	void FirstStage::OnUpdate() {
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		if (!player->GetDrawActive())
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			return;
		}
		if (time->GetTimeLeft() <= 0.0f)
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			return;
		}
	} // end OnUpdate

	void FirstStage::OnDraw()
	{
		Stage::OnDraw();
		App::GetApp()->GetScene<Scene>()->SetDebugString(L"");
	}

}
//end basecross
