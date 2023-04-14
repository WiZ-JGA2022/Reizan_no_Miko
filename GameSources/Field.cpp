/*!
@file Ground.cpp
@brief �n�ʂ�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Field::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -5.5f, 0.0f);
		transComp->SetScale(1.0f, 1.0f, 1.0f);

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
		ptrShadow->SetMeshResource(L"STAGE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"STAGE");
		drawComp->SetMeshToTransformMatrix(spanMat);
	}

	void Field::OnUpdate()
	{
	}
	void Field2::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);
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
		ptrShadow->SetMeshResource(L"BOX");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"BOX");
		drawComp->SetMeshToTransformMatrix(spanMat);
	}

	void Field2::OnUpdate()
	{
	}
}
//end basecross
