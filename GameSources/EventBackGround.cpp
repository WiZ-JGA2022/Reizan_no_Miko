/* !
@file EventBackGround.h
@brief LevelUpEvent実行中の背景
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EventBackGround::EventBackGround(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	EventBackGround::~EventBackGround() {}

	void EventBackGround::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		m_vertices = {
			{Vec3(0.0f				, 0.0f				, 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(m_DefaultSize.x	, 0.0f				, 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(0.0f				, -m_DefaultSize.y	, 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(m_DefaultSize.x	, -m_DefaultSize.y	, 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"EVENT_BACK_GROUND");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f);

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void EventBackGround::OnUpdate()
	{
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec();					// ステージに追加されているすべてのオブジェクト
		
		// 処理終了後に表示した画像を消す処理
		for (auto& obj : objs)
		{
			// LevelUpButtonへのキャストを試みる
			auto levelUpButton = dynamic_pointer_cast<RandomSelectLevelUpButton>(obj);
			if (levelUpButton)
			{
				auto controllerKeyFlg = levelUpButton->GetEventActive();
				if (!controllerKeyFlg) {
					GetStage()->RemoveGameObject<EventBackGround>(GetThis<EventBackGround>());
				}
			}
		}
	}
}