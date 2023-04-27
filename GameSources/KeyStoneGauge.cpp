
/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	�����̃X�N�G�A
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	KeyStoneGauge::KeyStoneGauge(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<KeyStone>& SeekObjectPtr) :
		GameObject(StagePtr),
		m_keyStoneHp(SeekObjectPtr)
	{}
	KeyStoneGauge::~KeyStoneGauge() {}

	//������
	void KeyStoneGauge::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_keyStoneHp.expired()) {
			auto SeekPtr = m_keyStoneHp.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 3.0f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());

			const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

			m_vertices = {
				{Vec3(-m_DefaultSize.x * 0.5f, 0.0f			   , 0.0f), white, Vec2(0.0f, 0.0f)},
				{Vec3(m_DefaultSize.x * 0.5f , 0.0f			   , 0.0f), white, Vec2(0.1f, 0.0f)},
				{Vec3(-m_DefaultSize.x * 0.5f, -m_DefaultSize.y, 0.0f), white, Vec2(0.0f, 1.0f)},
				{Vec3(m_DefaultSize.x * 0.5f , -m_DefaultSize.y, 0.0f), white, Vec2(0.1f, 1.0f)},
			};
			m_indices = {
				0, 1, 2,
				2, 1, 3
			};

			m_draw = AddComponent<PCTStaticDraw>();
			m_draw->SetOriginalMeshUse(true);
			m_draw->CreateOriginalMesh(m_vertices,m_indices);
			m_draw->SetTextureResource(L"HPBAR_GREEN");
			SetAlphaActive(true);
			SetDrawLayer((int)DrawLayer::Bottom);
		}

	}


	//�ω�
	void KeyStoneGauge::OnUpdate() {

		if (!m_keyStoneHp.expired()) {

			auto transform = GetComponent<Transform>();
			auto stonePtr = m_keyStoneHp.lock();
			auto cameraPtr = GetStage()->GetView()->GetTargetCamera();
			// �Q�[�W�̑傫�����X�V
			UpdateGaugeSize(stonePtr->GetMaxHp(), stonePtr->GetCurrentHp());

			//�������r���{�[�h�ɂ���
			Quat Qt;
			Qt = Billboard(cameraPtr->GetAt() - cameraPtr->GetEye());
			transform->SetQuaternion(Qt);
		}

	}

	void KeyStoneGauge::UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize)
	{
		float gaugeSizeDiff = m_DefaultSize.x / gaugeSizeLimit;
		for (int i = 0; i < 4; i++)
		{
			float currentLostGauge = gaugeSizeLimit - currentGaugeSize;
			if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
			{
				m_vertices[i].position.x = m_DefaultSize.x * 0.5f - (gaugeSizeDiff * currentLostGauge);
			}
		}

		m_draw->UpdateVertices(m_vertices);

	}


}