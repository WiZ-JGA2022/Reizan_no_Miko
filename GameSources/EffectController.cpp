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
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
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
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// �J�����s���ݒ�
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring efect01 = dataDir + L"Lava.efk";
		wstring efect02 = dataDir + L"fire02.efk";

		m_effect = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect01.c_str());
		m_effect2 = ::Effekseer::Effect::Create(m_manager, (const char16_t*)efect02.c_str());

	}

	void EffectController::OnUpdate() {

	}

	void EffectController::OnDraw() {
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

		auto elps = App::GetApp()->GetElapsedTime();
		if (m_TotalTime <= 0.0f) {
			//m_handle = m_manager->Play(m_effect, 0, 5, 0);
			m_handle = m_manager->Play(m_effect, playerPos.x, playerPos.y+ 10, playerPos.z);
		}
		else if (m_TotalTime >= 30.0f) {
			m_manager->StopEffect(m_handle);
		}
		m_TotalTime += elps;

		m_manager->Update();// �}�l�[�W���[�̍X�V		
		m_renderer->SetTime(elps);// ���Ԃ��X�V����
		m_renderer->BeginRendering();// �G�t�F�N�g�̕`��J�n�������s���B
		m_manager->Draw();// �G�t�F�N�g�̕`����s���B
		m_renderer->EndRendering();// �G�t�F�N�g�̕`��I���������s���B
	}
	void EffectController::OnDraw2() {
		auto playerTrans = GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition(); // �v���C���[�̈ʒu�x�N�g�����擾

		auto elps = App::GetApp()->GetElapsedTime();
		if (m_TotalTime <= 0.0f) {
			//m_handle = m_manager->Play(m_effect, 0, 5, 0);
			m_handle = m_manager->Play(m_effect2, playerPos.x, playerPos.y+ 10, playerPos.z);
		}
		else if (m_TotalTime >= 30.0f) {
			m_manager->StopEffect(m_handle);
		}
		m_TotalTime += elps;

		m_manager->Update();// �}�l�[�W���[�̍X�V		
		m_renderer->SetTime(elps);// ���Ԃ��X�V����
		m_renderer->BeginRendering();// �G�t�F�N�g�̕`��J�n�������s���B
		m_manager->Draw();// �G�t�F�N�g�̕`����s���B
		m_renderer->EndRendering();// �G�t�F�N�g�̕`��I���������s���B
	}

	void EffectController::OnDestroy() {

		// Dispose the manager
		// �}�l�[�W���[�̔j��
		m_manager.Reset();

		// Dispose the renderer
		// �����_���[�̔j��
		m_renderer.Reset();
	}

}
//end basecross
