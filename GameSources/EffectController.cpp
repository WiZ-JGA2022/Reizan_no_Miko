/*!
@file EffectController.cpp
@brief �G�t�F�N�g
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
		// �G�t�F�N�g�̃����_���[�̍쐬
		m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);

		// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
		m_manager = ::Effekseer::Manager::Create(8000);
		// �`�惂�W���[���̐ݒ�
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
		// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// ���_�ʒu���m��
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

		// ���e�s���ݒ�
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * XM_PI, w / h, 1.0f, 500.0f));
		// �J�����s���ݒ�
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
		m_manager->Update();// �}�l�[�W���[�̍X�V		
		m_renderer->SetTime(elps);// ���Ԃ��X�V����
		m_renderer->BeginRendering();// �G�t�F�N�g�̕`��J�n�������s��
		m_manager->Draw();// �G�t�F�N�g�̕`����s��
		m_renderer->EndRendering();// �G�t�F�N�g�̕`��I���������s��
	}

	void EffectController::OnDestroy() {

		// �}�l�[�W���[�̔j��
		m_manager.Reset();

		// �����_���[�̔j��
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

		m_manager->Update();			// �}�l�[�W���[�̍X�V
		m_renderer->SetTime(elps);		// ���Ԃ��X�V����
		m_renderer->BeginRendering();	// �G�t�F�N�g�̕`��J�n�������s��
		m_manager->Draw();				// �G�t�F�N�g�̕`����s��
		m_renderer->EndRendering();		// �G�t�F�N�g�̕`��I���������s��

	}
}
//end basecross
