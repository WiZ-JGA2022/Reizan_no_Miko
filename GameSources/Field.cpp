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
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -1.0f, 0.0f);
		//transComp->SetScale(1.0f, 1.0f, 1.0f);
		transComp->SetScale(100.0f, 1.0f, 100.0f);

		//Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		//spanMat.affineTransformation(
		//	Vec3(1.0f, 1.0f, 1.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);
		////�e������i�V���h�E�}�b�v��`�悷��j
		//auto ptrShadow = AddComponent<Shadowmap>();
		////�e�̌`�i���b�V���j��ݒ�
		//ptrShadow->SetMeshResource(L"STAGE");
		//ptrShadow->SetMeshToTransformMatrix(spanMat);

		//auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		//drawComp->SetFogEnabled(true);
		//drawComp->SetMeshResource(L"STAGE");
		//drawComp->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

	}

	void Field::OnUpdate()
	{
		//auto transComp = GetComponent<Transform>();
		//transComp->ResetPosition(Vec3(0.0f, -5.5f, 5.0f));
	}
}
//end basecross
