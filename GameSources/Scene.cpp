
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
		RoadTexture(L"HPBAR_GREEN", L"HpBar(Green).png");
		RoadTexture(L"HPBAR_RED", L"HpBar(Red).png");
		RoadTexture(L"HP_NUMBER", L"HpNumber.png");
		RoadTexture(L"TIME_NUMBER", L"TimeNumber.png");
		RoadTexture(L"TIME_CHARA", L"LeftTime.png");
		RoadTexture(L"TITLE", L"Title.png");
		RoadTexture(L"RESULT", L"Result.png");
		RoadTexture(L"GAME_SPRITE", L"EnemyActive.png");
		RoadTexture(L"STANDBY_PHASE", L"Standby.png");
		RoadTexture(L"CLEAR_SPRITE", L"Clear.png");
		RoadTexture(L"TRAP_1", L"罠1.png");
		RoadTexture(L"TRAP_2", L"罠2.png");
		RoadTexture(L"XBUTTON", L"Xボタン.png");
		RoadTexture(L"YBUTTON", L"Yボタン.png");
		RoadTexture(L"TRAP_NUMBER", L"TrapNumberUi.png");
		RoadTexture(L"START_UI", L"スタートUI.png");
		RoadTexture(L"TUTORIAL", L"チュートリアル(仮).png");
		RoadTexture(L"FADE_BLACK", L"Fade_Black.png");
		RoadTexture(L"FADE_WHITE", L"Fade_White.png");
		RoadTexture(L"RB_BUTTON", L"RBボタン.png");
		RoadTexture(L"HOLDBAR", L"HoldBar.png");
		RoadTexture(L"HOLDBARFRAME", L"HoldBarFrame.png");

		RoadSound(L"GAMECLEAR_BGM", L"GameClearBGM.wav");
		RoadSound(L"GAMEOVER_BGM", L"GameOverSE.wav");
		RoadSound(L"TITLE_BGM", L"TitleBGM.wav");
		RoadSound(L"STANDBY_BGM", L"StandbyStageBGM.wav");
		RoadSound(L"MAINGAME_BGM", L"GameStageBGM.wav");
		RoadSound(L"GAMECLEAR_SE", L"GameClearSE.wav");
		RoadSound(L"PLAYERDAMAGE_SE", L"PlayerTakenDamageSE.wav");
		RoadSound(L"SELECT_SE", L"SelectSE.wav");
		RoadSound(L"ENEMYDAMAGE_SE", L"EnemyKnockDownSE.wav");
		RoadSound(L"STONEDAMAGE_SE", L"StoneDamageSE.wav");
		RoadSound(L"SPIKE_SE", L"SpikeSE.wav");
		RoadSound(L"SPIKEDAMAGE_SE", L"SpikeDamageSE.wav");
		RoadSound(L"LAVA_SE", L"StaticLavaSE.wav");
		RoadSound(L"SPURTLAVA_SE", L"SpurtLavaSE.wav");
		RoadSound(L"COUNTDOWN_SE", L"CountDownSE.wav");
		RoadSound(L"SKIP_SE", L"SkipSE.wav");

		RoadStaticModelMesh(L"O_stage", L"STAGE");
		RoadStaticModelMesh(L"ofuda", L"OHUDA");
		RoadStaticModelMesh(L"Thorn", L"SPIKE_MODEL");
		RoadStaticModelMesh(L"O_trap", L"SPURTLAVA_MODEL");

		RoadBoneModel(L"O_miko_all", L"MIKO", L"MIKO_TAN");
		RoadBoneModel(L"O_oni_all", L"ONI", L"ONI_TAN");
		RoadBoneModel(L"O_stone_animation", L"STONE_MODEL", L"STONE_MODEL_TAN");
		RoadBoneModel(L"O_soul", L"SOUL_MODEL", L"SOUL_MODEL_TAN");

	}

	void Scene::OnCreate(){
		try {
			//エフェクト作成
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();
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

	void Scene::OnUpdate()
	{
		SceneBase::OnUpdate();
		m_EfkInterface->OnUpdate();
	}

	void Scene::OnDraw()
	{
		SceneBase::OnDraw();
		auto& camera = GetActiveStage()->GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToFirstStage") {
			// アクティブステージの設定
			ResetActiveStage<FirstStage>();
		}
		else if (event->m_MsgStr == L"ToStandbyStage") {
			// アクティブステージの設定
			ResetActiveStage<StandbyStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			// アクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			// データのリセット
			ResetData();
			// アクティブステージの設定
			ResetActiveStage<ClearStage>();
		}
		else if (event->m_MsgStr == L"ToResultStage") {
			// データのリセット
			ResetData();
			// アクティブステージの設定
			ResetActiveStage<DefeatStage>();
		}
	}

	void Scene::ResetData()
	{
		// データの初期化
		for (int i = 0; i < 4; i++)
		{
			m_trapCount[i] = 0;
		}

		m_playerPosition = Vec3(0);
		m_playerRotation = Quat(0);
		m_cameraAt = Vec3(0);
		m_cameraAngle = XMConvertToRadians(270.0f);
		m_cameraRadXZ = 0.0f;
		m_cameraRadY = 0.0f;

		for (int i = 0; i < 5; i++)
		{
			m_spikePosition[i] = Vec3(0);
		}
		for (int i = 0; i < 1; i++)
		{
			m_lavaPosition[i] = Vec3(0);
		}

	}

}
//end basecross
