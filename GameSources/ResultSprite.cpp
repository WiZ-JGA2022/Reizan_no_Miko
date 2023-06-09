/* !
@file ResultSprite.cpp
@brief リザルトシーンの背景の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	ResultSprite::ResultSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// デストラクタ
	ResultSprite::~ResultSprite() {}

	// 初期化
	void ResultSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"GAMEOVER");
	}

	// 更新処理
	void ResultSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}

	// コンストラクタ
	ClearSprite::ClearSprite(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight()))
	{
	}
	// デストラクタ
	ClearSprite::~ClearSprite() {}

	// 初期化
	void ClearSprite::OnCreate()
	{
		Sprites::CreateSprite(Vec3(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f), m_DefaultSize, L"CLEAR_SPRITE");
	}

	// 更新処理
	void ClearSprite::OnUpdate()
	{
		Sprites::OnUpdate();
	}
}