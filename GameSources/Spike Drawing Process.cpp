/*!
@file Spike Drawing Process.cpp
@brief �X�p�C�N�̕`�揈���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SpikeModel::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position.x, m_position.y - 1.5f, m_position.z);
		transComp->SetScale(1.5f, 1.0f, 1.5f);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"SPIKE_MODEL");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"SPIKE_MODEL");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void SpikeModel::OnUpdate()
	{
		m_position.y += 0.1f;
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_position);

		if (m_position.y >= 20.0f)
		{
			GetStage()->RemoveGameObject<SpikeModel>(GetThis<SpikeModel>());
		}
	}
}
//end basecross
