/*!
@file Item.cpp
@brief アイテムの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	void Item::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		//ptrTrans->SetScale(Vec3(0.5f, 0.5f, 0.5f));
		//Quat Qt;
		//Qt.identity();
		//ptrTrans->SetQuaternion(Qt);
		//ptrTrans->SetPosition(m_startPos);


		//Itemのコンポーネント設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_itemScale);//大きさ
		transComp->SetPosition(0.0f, 0.0f, 0.0f);//位置

		////衝突判定をつける
		//auto PtrCol = AddComponent<CollisionObb>();
		////衝突判定はNoneにする
		//PtrCol->SetAfterCollision(AfterCollision::None);

		////物理計算ボックス
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(true);


		////ステートマシンの構築
		//m_stateMachine.reset(new StateMachine<Item>(GetThis<Item>()));

	}

	Vec3 Item::GetTargetPos()const {
		auto targetPtr = GetStage()->GetSharedObject(L"Player");
		return targetPtr->GetComponent<Transform>()->GetPosition();
	}

	void Item::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_itemMoveSpeed += m_itemForce * elapsedTime;
		auto ptrTransform = GetComponent<Transform>();
		auto pos = ptrTransform->GetPosition();
		pos += m_itemMoveSpeed * elapsedTime;
		ptrTransform->SetPosition(pos);
	}



	void Item::OnUpdate()
	{		
		m_itemForce = Vec3(0);
		auto force = GetForce();
		SetForce(force);

	}	
	IMPLEMENT_SINGLETON_INSTANCE(ItemNearState)

		void ItemNearState::Enter(const shared_ptr<Item>& Obj) {
	}

	void ItemNearState::Execute(const shared_ptr<Item>& Obj) {
		auto ptrArrive = Obj->GetBehavior<ArriveSteering>();
		auto force = Obj->GetForce();
		force = ptrArrive->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		Obj->SetForce(force);
		Obj->ApplyForce();
		float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		if (f >= Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(ItemNearState::Instance());
		}
	}

	void ItemNearState::Exit(const shared_ptr<Item>& Obj) {
	}


	//プレイヤーとの距離を得る
	float Item::GetToPlayerLen() const {
		auto Ptr = GetComponent<Transform>();
		Vec3 Pos = Ptr->GetPosition();
		auto PlayerPos
			= GetStage()->GetSharedGameObject<PlayerController>(L"Player")->GetComponent<Transform>()->GetPosition();
		return length(Pos - PlayerPos);
	}
	//プレイヤーを追いかける行動
	void Item::SeekPlayerBehavior() {
		auto PsPtr = GetComponent<RigidbodyBox>();
		PsPtr->WakeUp();
		auto TargetPtr = GetStage()->GetSharedObject(L"Player");
		auto TargetPos = TargetPtr->GetComponent<Transform>()->GetPosition();
		auto Pos = GetComponent<Transform>()->GetPosition();
		TargetPos.y = Pos.y = m_startPos.y;
		bsm::Vec3 WorkForce;
		WorkForce = Steering::Seek(Vec3(0), TargetPos,
			Pos, 20.0f) * 1.0f;
		PsPtr->ApplyForce(WorkForce);
	}

}
//end basecross
