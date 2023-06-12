/*!
@file ClearStage.cpp
@brief �Q�[���������̃X�e�[�W�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�N���A�X�e�[�W�N���X
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
		m_bgm = XAPtr->Start(L"GAMECLEAR_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void ClearStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	//������
	void ClearStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateResultSprite();
		AddGameObject<FadeIn>(L"FADE_WHITE");
		PlayBGM();
	} // end OnCreate

	//�X�V
	void ClearStage::OnUpdate() {
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
		m_inputHandler.PushHandle(GetThis<ClearStage>());

	} // end OnUpdate

	//B�{�^��
	void ClearStage::OnPushB() {
		AddGameObject<FadeOut>(L"FADE_WHITE");

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB

}