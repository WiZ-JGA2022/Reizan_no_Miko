/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
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
		m_bgm = XAPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void TitleStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	//������
	void TitleStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		AddGameObject<FadeIn>(L"FADE_BLACK");

		PlayBGM();

	} // end OnCreate

	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_inputHandler.PushHandle(GetThis<TitleStage>());

	} // end OnUpdate

	//B�{�^��
	void TitleStage::OnPushB() {
		if (m_start)
		{
			return;
		}
		AddGameObject<FadeOut>(L"FADE_WHITE");

		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"SELECT_SE", 0, 0.5f);
		PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");
		m_start = true;
	} // end OnPushB
}