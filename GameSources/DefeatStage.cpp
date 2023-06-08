/*!
@file DefeatStage.cpp
@brief �Q�[���s�k���̃X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void DefeatStage::CreateViewLight() {
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
	void DefeatStage::CreateResultSprite() {
		AddGameObject<ResultSprite>();
	} // end CreateResultSprite

	void DefeatStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_bgm = XAPtr->Start(L"GAMEOVER_BGM", 0, 0.3f);
	}

	void DefeatStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	//������
	void DefeatStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateResultSprite();
		AddGameObject<FadeIn>(L"FADE_BLACK");
		PlayBGM();
	} // end OnCreate

	//�X�V
	void DefeatStage::OnUpdate() {
		// �f�o�C�X�̎擾
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		// ���Z�b�g�R�}���h
		if (pad.wButtons & XINPUT_GAMEPAD_START && pad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			// �^�C�g���ɖ߂�
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
		}

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_inputHandler.PushHandle(GetThis<DefeatStage>());

	} // end OnUpdate

	//B�{�^��
	void DefeatStage::OnPushB() {
		AddGameObject<FadeOut>(L"FADE_BLACK");

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB
}