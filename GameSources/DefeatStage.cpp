/*!
@file DefeatStage.cpp
@brief ゲーム敗北時のステージの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	void DefeatStage::CreateViewLight() {
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
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_bgm);
	}

	//初期化
	void DefeatStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateResultSprite();
		AddGameObject<FadeIn>(L"FADE_BLACK");
		PlayBGM();
	} // end OnCreate

	//更新
	void DefeatStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_inputHandler.PushHandle(GetThis<DefeatStage>());

	} // end OnUpdate

	//Bボタン
	void DefeatStage::OnPushB() {
		AddGameObject<FadeOut>(L"FADE_BLACK");

		PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	} // end OnPushB
}