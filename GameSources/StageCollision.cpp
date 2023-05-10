/*!
@file StageCollision.cpp
@brief 地面を表すクラスの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageCollision::StageCollision(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision::~StageCollision() {}

	void StageCollision::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(1.0f, 10.0f, 90.0f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision::OnUpdate()
	{
	};

	StageCollision2::StageCollision2(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision2::~StageCollision2() {}

	void StageCollision2::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(1.0f, 10.0f, 90.0f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision2::OnUpdate()
	{
	};

	StageCollision3::StageCollision3(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision3::~StageCollision3() {}

	void StageCollision3::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(60.0f, 10.0f, 1.0f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision3::OnUpdate()
	{
	};

	StageCollision4::StageCollision4(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision4::~StageCollision4() {}

	void StageCollision4::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(28.0f, 3.0f, 7.5f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision4::OnUpdate()
	{
	};

	StageCollision5::StageCollision5(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision5::~StageCollision5() {}

	void StageCollision5::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(31.0f, 3.0f, 6.5f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision5::OnUpdate()
	{
	};

	StageCollision6::StageCollision6(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision6::~StageCollision6() {}

	void StageCollision6::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(5.0f, 3.0f, 16.0f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision6::OnUpdate()
	{
	};

	StageCollision7::StageCollision7(const std::shared_ptr<Stage>& stage, const Vec3& position) :
		GameObject(stage),
		m_position(position)
	{
	}
	StageCollision7::~StageCollision7() {}

	void StageCollision7::OnCreate()
	{
		auto collComp = AddComponent<CollisionObb>();
		collComp->SetDrawActive(true);
		// 衝突判定はAuto
		collComp->SetAfterCollision(AfterCollision::Auto);
		collComp->SetSleepActive(false);
		collComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(5.0f, 3.0f, 14.5f);

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
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetFogEnabled(true);
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetMeshToTransformMatrix(spanMat);

		SetDrawLayer((int)DrawLayer::MostBottom);
	}

	void StageCollision7::OnUpdate()
	{
	};
}