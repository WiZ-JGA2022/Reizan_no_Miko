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
		const Vec3 at(0.0f);
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

	void GameStage::OnCreate() {
		try {
			auto& app = App::GetApp();

			auto mediaPath = app->GetDataDirWString();
			auto texturePath = mediaPath + L"Textures/";

			app->RegisterTexture(L"EXPBAR_BLACK", texturePath + L"ExpBar(Black).png");
			app->RegisterTexture(L"EXPBAR_BLUE", texturePath + L"ExpBar(Blue).png");
			app->RegisterTexture(L"HPBAR_GREEN", texturePath + L"HpBar(Green).png");
			app->RegisterTexture(L"HPBAR_RED", texturePath + L"HpBar(Red).png");

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
