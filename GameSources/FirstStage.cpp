/*!
@file FirstStage.cpp
@brief �Q�[���X�e�[�W����
@prod ��I�t
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


	//�v���C���[�̍쐬
	void FirstStage::CreatePlayer() {
		// �X�^���o�C�X�e�[�W�I�����̏����擾
		Vec3 beforePlayerPosition = App::GetApp()->GetScene<Scene>()->GetBeforePlayerPosition();
		Quat beforePlayerQuaternion = App::GetApp()->GetScene<Scene>()->GetBeforePlayerQuaternion();

		// �������Ɉʒu�Ɖ�]�̏������
		auto player = AddGameObject<PlayerController>(beforePlayerPosition, beforePlayerQuaternion, 1);
		SetSharedGameObject(L"Player", player);
		player->AddTag(L"Player");
		auto statusController = AddGameObject<PlayerStatusController>();
		SetSharedGameObject(L"PlayerStatus", statusController);
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_RED");
		AddGameObject<PlayerHpGauge>(statusController, L"HPBAR_GREEN");
	} // end CreatePlayer	

	void FirstStage::CreateUI()
	{
		// Hp�o�[�̍쐬
		AddGameObject<HpBar>();

		// Hp�̐����\�L���쐬
		AddGameObject<HpNumber>();

		AddGameObject<StrengthSprite>();

		AddGameObject<RightStick>();

		// �c�莞�Ԃ̕\��UI���쐬
		auto time = AddGameObject<TimeNumber>(m_TotalTimeSeconds, false,false);
		SetSharedGameObject(L"Time", time);
		
		AddGameObject<TimeChara>();

		AddGameObject<GameSprite>();
	} // end CreateUI

	void FirstStage::PlayBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_bgm = XAPtr->Start(L"MAINGAME_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}

	void FirstStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	void FirstStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[���[�̍쐬
			CreatePlayer();
			// �G�̍쐬
			CreateEnemy();

			// �n�ʂ̍쐬
			AddGameObject<Field>();
			auto stone = AddGameObject<KeyStone>();
			SetSharedGameObject(L"KeyStone", stone);
			AddGameObject<StageCollision>(Vec3(30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(-30.4f, 4.5f, 29.0f), Vec3(1.0f, 10.0f, 90.0f));
			AddGameObject<StageCollision>(Vec3(0.0f, 4.5f, -16.0f), Vec3(60.0f, 10.0f, 1.0f));
			AddGameObject<StageCollision>(Vec3(-16.0f, 1.0f, 7.5f), Vec3(28.0f, 3.0f, 8.5f));
			AddGameObject<StageCollision>(Vec3(14.5f, 1.0f, 26.0f), Vec3(31.5f, 3.0f, 6.5f));
			AddGameObject<StageCollision>(Vec3(7.5f, 1.0f, 53.0f), Vec3(3.0f, 3.0f, 18.0f));
			AddGameObject<StageCollision>(Vec3(-8.0f, 1.0f, 52.0f), Vec3(3.0f, 3.0f, 16.5f));

			// �V�[���̎擾
			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			// �X�^���o�C�X�e�[�W��㩂��ݒu����Ă��鎞�̂݃��[�v����
			for (int i = 0; i < scene->GetBeforePlacedTrap(0); i++)
			{
				// ��㩂̐���
				AddGameObject<SpikeTrap>(scene->GetBeforeSpikePosition(i), Vec3(5.0f, 0.5f, 5.0f));
			}
			for (int i = 0; i < scene->GetBeforePlacedTrap(1); i++)
			{
				// �n��㩂̐���
				AddGameObject<SpurtLava>(scene->GetBeforeLavaPosition(i), Vec3(4.0f, 20.0f, 4.0f));
			}

			// UI�̍쐬
			CreateUI();
			PlayBGM();

			// �v���C���[�ƃJ�������擾
			auto player = GetSharedGameObject<PlayerController>(L"Player");
			auto& camera = GetView()->GetTargetCamera();
			auto myCamera = dynamic_pointer_cast<MyCamera>(camera);
			// ���C���J�����̃^�[�Q�b�g�Ƀv���C���[���Z�b�g����
			myCamera->SetTargetObject(player);
		}
		catch (...) {
			throw;
		}
	}

	//�X�V
	void FirstStage::OnUpdate() {
		// �e����̎擾
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto& device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		auto player = GetSharedGameObject<PlayerController>(L"Player");
		auto time = GetSharedGameObject<TimeNumber>(L"Time");
		
		// ���Z�b�g�R�}���h�������ꂽ��
		if (pad.wButtons & XINPUT_GAMEPAD_START && pad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			// �X�e�[�W�ύX�t���O���I��
			m_isChangeStage = true;
			// �^�C�g���ɖ߂�
			PostEvent(0.1f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
		}

		// �v���C���[���`�悳��Ȃ��Ȃ�����
		if (!player->GetDrawActive())
		{
			// �X�e�[�W�ύX�t���O���I��
			m_isChangeStage = true;
			// Defeat�X�e�[�W�Ɉړ�
			AddGameObject<FadeOut>(L"FADE_BLACK");
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDefeatStage");
			return;
		}
		// ���Ԑ؂�ɂȂ�����
		if (time->GetTimeLeft() <= 0.0f)
		{
			// �X�e�[�W�ύX�t���O���I��
			m_isChangeStage = true;
			// Clear�X�e�[�W�Ɉړ�
			AddGameObject<FadeOut>(L"FADE_WHITE");
			PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			return;
		}
	} // end OnUpdate
}
//end basecross
