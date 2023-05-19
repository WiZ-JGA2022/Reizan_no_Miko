/*!
@file EffectController.cpp
@brief エフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")

	void EffectController::OnCreate()
	{
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
		// エフェクトのレンダラーの作成
		m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);

		// エフェクトのマネージャーの作成
		m_manager = ::Effekseer::Manager::Create(8000);
		// 描画モジュールの設定
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// 視点位置を確定
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

		// 投影行列を設定
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * XM_PI, w / h, 1.0f, 500.0f));
		// カメラ行列を設定
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring efect01 = dataDir + L"Effects\\" + L"Lava.efk";
		wstring efect02 = dataDir + L"Effects\\" + L"fire04.efk";
		wstring efect03 = dataDir + L"Effects\\" + L"RunDust.efk";
		wstring efect04 = dataDir + L"Effects\\" + L"damage.efk";

		m_effects[L"SpurtLava_Efc"] = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect01.c_str());
		m_effects[L"FireBall_Efc"] = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect02.c_str());
		m_effects[L"RunDust_Efc"] = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect03.c_str());
		m_effects[L"Damage_Efc"] = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect04.c_str());

	}

	void EffectController::OnUpdate() {

	}

	void EffectController::OnDraw() {
		auto elps = App::GetApp()->GetElapsedTime();
		m_manager->Update();// マネージャーの更新		
		m_renderer->SetTime(elps);// 時間を更新する
		m_renderer->BeginRendering();// エフェクトの描画開始処理を行う
		m_manager->Draw();// エフェクトの描画を行う
		m_renderer->EndRendering();// エフェクトの描画終了処理を行う
	}

	void EffectController::OnDestroy() {

		// マネージャーの破棄
		m_manager.Reset();

		// レンダラーの破棄
		m_renderer.Reset();
	}

	void EffectController::PlayEffect(const wstring& effectKey, const Vec3& position, const float stopTime)
	{
		auto elps = App::GetApp()->GetElapsedTime();
		if (m_totalTime <= 0.0f) {
			m_handle = m_manager->Play(m_effects[effectKey], position.x, position.y, position.z);
			//m_handle = m_manager->Play(m_effects[effectKey], -20.0f, 0.0f, -20.0f);
		}
		else if (m_totalTime >= stopTime) {
			m_manager->StopEffect(m_handle);
		}
		m_totalTime += elps;

		m_manager->Update();			// マネージャーの更新
		m_renderer->SetTime(elps);		// 時間を更新する
		m_renderer->BeginRendering();	// エフェクトの描画開始処理を行う
		m_manager->Draw();				// エフェクトの描画を行う
		m_renderer->EndRendering();		// エフェクトの描画終了処理を行う

	}
}
//end basecross
