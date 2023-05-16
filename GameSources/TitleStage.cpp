/*!
@file TitleStage.cpp
@brief タイトルステージの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	} // end CreateViewLight

	//スプライトの作成
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
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//初期化
	void TitleStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();

		PlayBGM();

	} // end OnCreate

	//更新
	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());

	} // end OnUpdate

	//Bボタン
	void TitleStage::OnPushB() {
		AddGameObject<FadeOut>(L"FADE_WHITE");

		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"SELECT_SE", 0, 0.5f);
		PostEvent(2.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStandbyStage");

	} // end OnPushB
}