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
		transComp->SetScale(Vec3(0.5f));//大きさ
		transComp->SetPosition(1.0f, 0.0f, 0.0f);//位置

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

	//void Item::OnUpdate()
	//{		
		//auto& app = App::GetApp();

		////デルタタイムを取得
		//float delta = app->GetElapsedTime();

		//auto transComp = GetComponent<Transform>();
		//Vec3 Itempos = transComp->GetPosition();
		//Itempos += m_MoveSpeed * m_dir * delta;
		//transComp->SetPosition(Itempos);
		

		//プレイヤーが一定の距離内に来たらその方に移動する
		//if ()
		//{
		//	

		//}

		////Itemがプレイヤーの近くに来たら消す
		//if (Itempos.length() <1.0f && m_owner)//まだplayerの判定はできてないので1.0を入れている
		//{
		//	GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		//}


	//}	
	//更新
	//void Item::OnUpdate() 
	//{
	//	//ステートマシンのUpdateを行う
	//		//この中でステートの切り替えが行われる
	//		m_stateMachine->Update();
	//}

	//プレイヤーとの距離を得る
	float Item::GetToPlayerLen() const {
		auto Ptr = GetComponent<Transform>();
		Vec3 Pos = Ptr->GetPosition();
		auto PlayerPos
			= GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
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
