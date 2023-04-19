/*!
@file AttackAnnounce.cpp
@brief 攻撃予告スプライトの実装
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	AttackAnnounceCircle::AttackAnnounceCircle(const shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	AttackAnnounceCircle::~AttackAnnounceCircle() {}

	void AttackAnnounceCircle::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		m_vertices = {
			{Vec3(-0.5f	, 0.5f	, 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(0.5f	, 0.5f	, 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(-0.5f	, -0.5f	, 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(0.5f	, -0.5f	, 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);
		m_transform->SetScale(m_DefaultSize.x, m_DefaultSize.y, 0.0f);

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"ATTACK_ANNOUNCE_CIRCLE");


		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void AttackAnnounceCircle::OnUpdate()
	{

	}


	/*------------------------------------
	*	AttackAnnounceLineクラス
	 -----------------------------------*/
	AttackAnnounceLine::AttackAnnounceLine(const shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position),
		m_scale(0),
		m_coefficient(0)
	{
	}
	AttackAnnounceLine::~AttackAnnounceLine() {}

	void AttackAnnounceLine::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // 色を白(画像ファイルの色そのまま)に

		m_vertices = {
			{Vec3(-0.5f	, 0.5f	, 0.0f), white, Vec2(0.0f, 0.0f)}, // 左上
			{Vec3(0.5f	, 0.5f	, 0.0f), white, Vec2(1.0f, 0.0f)}, // 右上
			{Vec3(-0.5f	, -0.5f	, 0.0f), white, Vec2(0.0f, 1.0f)}, // 左下
			{Vec3(0.5f	, -0.5f	, 0.0f), white, Vec2(1.0f, 1.0f)}, // 右下
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PNTStaticDraw>();
		m_draw->SetMeshResource(L"DEFAULT_SPHERE");
		m_draw->SetTextureResource(L"ATTACK_ANNOUNCE_LINE");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position);
		m_transform->SetScale(m_scale);

		// 透過処理を有効にする
		SetAlphaActive(true);
	}

	void AttackAnnounceLine::OnUpdate()
	{
		auto gimmickController = GetStage()->GetSharedGameObject<TrapController>(L"TrapController");
		m_coefficient = ((float)gimmickController->GetDamageFlame() - (float)gimmickController->GetDamageDelay()) / (float)gimmickController->GetDamageFlame();

		m_scale = Vec3(m_DefaultSize.x * m_coefficient, m_DefaultSize.y, m_DefaultSize.z * m_coefficient);
		m_transform->SetScale(m_scale);
	}

}