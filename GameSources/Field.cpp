/*!
@file Field.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Field::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, -0.5f, 48.0f);
		transComp->SetScale(10.0f, 5.0f, 5.0f);
		
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"STAGE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(false);
		drawComp->SetMeshResource(L"STAGE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void Field::OnUpdate()
	{
	}

	//要石
	void KeyStone::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(Vec3(0.0f, 0.0f, -12.0f));
		transComp->SetRotation(0.0f, 0.0f, 0.0f);
		transComp->SetScale(5.0f, 5.0f, 5.0f);

		AddTag(L"KeyStone");

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetTextureResource(L"STONE");

		//Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		//spanMat.affineTransformation(
		//	Vec3(1.0f, 1.0f, 1.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);
		////影をつける（シャドウマップを描画する）
		//auto ptrShadow = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//ptrShadow->SetMeshResource(meshKey);
		//ptrShadow->SetMeshToTransformMatrix(spanMat);

		////描画コンポーネントの設定
		//auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		//drawComp->SetFogEnabled(false);
		//drawComp->SetMeshResource(meshKey);
		//drawComp->SetMeshToTransformMatrix(spanMat);


		SetDrawLayer((int)DrawLayer::MostBottom);
	}


	void KeyStone::OnUpdate()
	{
		m_delay--;
		if (m_delay <= 0)
		{
			auto drawComp = GetComponent<PNTStaticDraw>();
			drawComp->SetEmissive(Col4(0.6f, 0.6f, 0.6f, 1.0f)); // Normalカラー
		}
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		if (m_hp <= 0)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
		}
	}

	void KeyStone::DamageProcess()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"STONEDAMAGE_SE", 0, 0.5f);
		auto drawComp = GetComponent<PNTStaticDraw>();
		drawComp->SetEmissive(Col4(1.0f, 0.2f, 0.2f, 1.0f));
		m_delay = m_DefaultDelay;
		m_hp -= 10.0f;
	}

}
//end basecross
