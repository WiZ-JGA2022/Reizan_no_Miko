
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	
	//!テクスチャの読み込み
	void Scene::RoadTexture(const wstring& TextureName, const wstring& UseTextureName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Texture\\" + TextureName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	void Scene::CreateResourses()
	{
		RoadTexture(L"EXPBAR_BLACK", L"ExpBar(Black).png");
		RoadTexture(L"EXPBAR_BLUE", L"ExpBar(Blue).png");
		RoadTexture(L"HPBAR_GREEN", L"HpBar(Green).png");
		RoadTexture(L"HPBAR_RED", L"HpBar(Red).png");

	}

	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
