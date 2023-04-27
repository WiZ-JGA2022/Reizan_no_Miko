
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
			//�ύX�ł���X�N�G�A���\�[�X���쐬

			//���_�z��
			//�C���f�b�N�X���쐬���邽�߂̔z��
			//vector<uint16_t> indices;
			////Square�̍쐬(�w���p�[�֐��𗘗p)
			//MeshUtill::CreateSquare(1.0f, m_vertices, indices);
			////���㒸�_
			//m_vertices[0].textureCoordinate = Vec2(0,0);
			////�E�㒸�_
			//m_vertices[1].textureCoordinate = Vec2(1.0f, 0);
			////�������_
			//m_vertices[2].textureCoordinate = Vec2(0, 1.0f);
			////�E�����_
			//m_vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			////���_�̌^��ς����V�������_���쐬
			//vector<VertexPositionColorTexture> new_vertices;
			//for (auto& v : m_vertices) {
			//	VertexPositionColorTexture nv;
			//	nv.position = v.position;
			//	nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			//	nv.textureCoordinate = v.textureCoordinate;
			//	new_vertices.push_back(nv);
			//}
			//�V�������_���g���ă��b�V�����\�[�X�̍쐬
			//m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			const Col4 white(1.0f, 1.0f, 1.0f, 1.0f);

			m_vertices = {
				{Vec3(-m_DefaultSize.x * 0.5f,0.0f,0.0f),white,Vec2(0.0f,0.0f)},
				{Vec3(m_DefaultSize.x * 0.5f,0.0f,0.0f),white,Vec2(0.1f,0.0f)},
				{Vec3(-m_DefaultSize.x * 0.5f,-m_DefaultSize.y,0.0f),white,Vec2(0.0f,1.0f)},
				{Vec3(m_DefaultSize.x * 0.5f,-m_DefaultSize.y,0.0f),white,Vec2(0.1f,1.0f)},
			};
			m_indices = {
				0,1,2,
				2,1,3
			};

			m_draw = AddComponent<PCTStaticDraw>();
			//m_draw->SetMeshResource(m_SquareMeshResource);
			m_draw->SetOriginalMeshUse(true);
			m_draw->CreateOriginalMesh(m_vertices,m_indices);
			m_draw->SetTextureResource(L"HPBAR_GREEN");
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//�ω�
	void KeyStoneGauge::OnUpdate() {

		if (!m_keyStoneHp.expired()) {
			auto SeekPtr = m_keyStoneHp.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();

			auto stone = GetStage()->GetSharedGameObject<KeyStone>(L"KeyStone");
			UpdateGaugeSize(stone->GetMaxHp(), stone->GetCurrentHp());
			//m_draw->UpdateVertices(m_vertices);


			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();


			Quat Qt;
			//�������r���{�[�h�ɂ���
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

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