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
		m_BGM = XAPtr->Start(L"GAMEOVER_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void DefeatStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//������
	void DefeatStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateResultSprite();
		PlayBGM();
	} // end OnCreate

	//�X�V
	void DefeatStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<DefeatStage>());

	} // end OnUpdate

	//B�{�^��
	void DefeatStage::OnPushB() {
		AddGameObject<FadeOut>(L"FADE_BLACK");

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB
}