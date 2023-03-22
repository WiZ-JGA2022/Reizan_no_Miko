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
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f, 1.0f ,0.0f);

		auto PtrView = CreateView<SingleView>();
		
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//�ǂ�������I�u�W�F�N�g�̍쐬
	void GameStage::CreateSeekObject() {
		//�I�u�W�F�N�g�̃O���[�v���쐬����
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		//�z��̏�����
		vector<Vec3> vec = {
			{ 0, 0.125f, 10.0f },
			{ 10.0f, 0.125f, 0.0f },
			{ -10.0f, 0.125f, 0.0f },
			{ 0, 0.125f, -10.0f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		for (size_t count = 0; count < vec.size(); count++) {
			auto Ptr = AddGameObject<SeekObject>(vec[count]);
		}

	}

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}


	void GameStage::OnCreate() {
		try {

			auto& app = App::GetApp();

			auto mediaPath = app->GetDataDirWString();
			auto texturePath = mediaPath + L"Textures/";

			app->RegisterTexture(L"EXPBAR_BLACK", texturePath + L"ExpBar(Black).png");
			app->RegisterTexture(L"EXPBAR_BLUE", texturePath + L"ExpBar(Blue).png");
			app->RegisterTexture(L"HPBAR_GREEN", texturePath + L"HpBar(Green).png");
			app->RegisterTexture(L"HPBAR_RED", texturePath + L"HpBar(Red).png");

			CreateSeekObject();
			CreatePlayer();
			//AddGameObject<SeekObject>(Vec3(1,0,0));

			auto player = AddGameObject<PlayerController>();


			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// Exp�o�[��Hp�o�[�̍쐬
			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();

			// �n�ʂ̍쐬
			AddGameObject<Field>();

			// ���C���J�����Ƀv���C���[���Z�b�g����
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			if (maincamera) // �G���[�`�F�b�N
			{
				maincamera->SetTarget(player);
			}

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
