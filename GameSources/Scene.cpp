
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
	
	// テクスチャの読み込み
	void Scene::RoadTexture(const wstring& UseTextureName, const wstring& TextureName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Textures\\" + TextureName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	void Scene::CreateResourses()
	{
		RoadTexture(L"EXPBAR_BLACK", L"ExpBar(Black).png");
		RoadTexture(L"EXPBAR_BLUE", L"ExpBar(Blue).png");
		RoadTexture(L"HPBAR_GREEN", L"HpBar(Green).png");
		RoadTexture(L"HPBAR_RED", L"HpBar(Red).png");
		RoadTexture(L"HP_LEVELUP", L"体力UP.png");
		RoadTexture(L"ATK_LEVELUP", L"攻撃力UP.png");
		RoadTexture(L"DEF_LEVELUP", L"防御力UP.png");
		RoadTexture(L"SPD_LEVELUP", L"移動速度UP.png");
		RoadTexture(L"HASTE_LEVELUP", L"攻撃速度UP.png");
		RoadTexture(L"PICKUP_LEVELUP", L"取得範囲UP.png");
		RoadTexture(L"WEPON_1_LEVELUP", L"武器1.png");
		RoadTexture(L"WEPON_2_LEVELUP", L"武器2.png");
	}

	void Scene::OnCreate(){
		try {
			// リソースの取得
			CreateResourses();
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
