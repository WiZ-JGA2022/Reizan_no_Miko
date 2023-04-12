/*!
@file Ground.cpp
@brief �n�ʂ�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Field::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::None);
		collComp->SetSleepActive(false);

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
		//ptrShadow->SetMeshResource(L"MODEL_MESH");
		//ptrShadow->SetMeshToTransformMatrix(spanMat);

		//auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		//drawComp->SetFogEnabled(true);
		//drawComp->SetMeshResource(L"FIELD");
		//drawComp->SetMeshToTransformMatrix(spanMat);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -1.0f, 0.0f);
		transComp->SetScale(60.0f, 1.0f, 200.0f);

	}

	void WallA::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(20.0f, 0.0f, 0.0f);
		transComp->SetScale(1.0f, 100.0f, 100.0f);
	}

	void WallA::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->ResetPosition(Vec3(20.0f, 0.0f, 0.0f));
	}

	void WallB::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);


		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(-20.0f, 0.0f, 0.0f);
		transComp->SetScale(1.0f, 100.0f, 100.0f);
	}

	void WallB::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->ResetPosition(Vec3(-20.0f, 0.0f, 0.0f));
	}

	void WallC::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);


		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, 0.0f, -20.0f);
		transComp->SetScale(100.0f, 100.0f, 1.0f);
	}

	void WallC::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->ResetPosition(Vec3(0.0f, 0.0f, -20.0f));
	}

	void BoxA::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);


		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(-7.5f, 0.0f, 10.0f);
		transComp->SetScale(30.0f, 5.0f, 5.0f);
	}

	void BoxA::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->ResetPosition(Vec3(-7.5f, 0.0f, 10.0f));
	}

	void BoxB::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"GROUND");

		auto collComp = AddComponent<CollisionObb>();
		// �Փ˔����Auto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);


		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(7.5f, 0.0f, 30.0f);
		transComp->SetScale(30.0f, 5.0f, 5.0f);
	}

	void BoxB::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->ResetPosition(Vec3(7.5f, 0.0f, 30.0f));
	}

}
//end basecross
