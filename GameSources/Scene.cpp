
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
	void Scene::RoadTexture(const wstring& UseTextureName, const wstring& TextureDataName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Textures\\" + TextureDataName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	// サウンドの読み込み
	void Scene::RoadSound(const wstring& soundName, const wstring& soundDataName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMusic = dataDir + L"Sounds\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}

	// 静的なモデルの読み込み
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,
			MeshResource::CreateStaticModelMesh(dataDir, L"MayaModels\\" + staticModelbmfName + L".bmf")
		);
	}

	// ボーンモデルの読み込み
	void Scene::RoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		App::GetApp()->RegisterResource(boneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir, L"MayaModels\\" + boneModelbmfName + L".bmf"));

		App::GetApp()->RegisterResource(boneModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModels\\" + boneModelbmfName + L".bmf")
		);

	}

	void Scene::CreateResourses()
	{
		// テスト用
		RoadTexture(L"WALL_TX", L"wall.jpg");

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
		RoadTexture(L"CROSSKEY_UP", L"CrossKey_Up.png");
		RoadTexture(L"CROSSKEY_RIGHT", L"CrossKey_Right.png");
		RoadTexture(L"CROSSKEY_DOWN", L"CrossKey_Down.png");
		RoadTexture(L"HP_NUMBER", L"HpNumber.png");
		RoadTexture(L"EXP_NUMBER", L"ExpNumber.png");
		RoadTexture(L"TIME_NUMBER", L"TimeNumber.png");
		RoadTexture(L"TIME_CHARA", L"LeftTime.png");
		RoadTexture(L"GROUND", L"ground.jpg");
		RoadTexture(L"EVENT_BACK_GROUND", L"EventBackGround.png");
		RoadTexture(L"ATTACK_ANNOUNCE_CIRCLE", L"AttackAnnouncementCircle.png");
		RoadTexture(L"ATTACK_ANNOUNCE_LINE", L"AttackAnnouncementLine.png");
		RoadTexture(L"TITLE", L"Title.png");
		RoadTexture(L"RESULT", L"Result.png");


		RoadSound(L"GAMECLEAR_BGM", L"GameClearBGM_long.wav");
		RoadSound(L"GAMEOVER_BGM", L"GameOverBGM.wav");
		RoadSound(L"TITLE_BGM", L"TitleBGM.wav");
		RoadSound(L"MAINGAME_BGM", L"INGameBGM.wav");
		RoadSound(L"EXP_SE", L"ExpSE.wav");
		RoadSound(L"FALLROCK_SE", L"FallingRockSE.wav");
		RoadSound(L"GAMECLEAR_SE", L"GameClearSE.wav");
		RoadSound(L"GAMEOVER_SE", L"GameOverSE.wav");
		RoadSound(L"LEVELUP_SE", L"LevelUp2SE.wav");
		RoadSound(L"PLAYERRUN_SE", L"PlayerRunSE.wav");
		RoadSound(L"PLAYERWALK_SE", L"PlayerWalkSE.wav");
		RoadSound(L"PLAYERDAMAGE_SE", L"PlayerTakenDamageSE.wav");
		RoadSound(L"SELECT_SE", L"Select2SE.wav");
		RoadSound(L"ENEMYDAMAGE_SE", L"EnemyKnockDownSE.wav");

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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
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
		else if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToResultStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<ResultStage>();
		}

		// デバッグ用文字列オブジェクトに対する設定
		auto dss = GetDebugStringSprite();
		dss->SetFontColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		dss->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		dss->SetStartPosition(Point2D<float>(1280 - 400.0f - 20.0f, 550.0f));
		dss->SetTextBlockWidth(400.0f);
		dss->SetTextBlockHeight(200.0f);
	}

}
//end basecross
