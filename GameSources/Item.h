/*!
@file Item.h
@brief アイテムの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item : public GameObject {

		//	std::shared_ptr<Transform> m_transform;

		//	Vec3 m_dir;//移動方向
		//	float m_MoveSpeed;//移動速度
		//	float m_pickUpArea;//ポップする範囲
		//	bool m_inArea;//プレイヤーの取得する時のフラグ

		//	shared_ptr<Player>m_owner;


		//public:
		//	Item(const std::shared_ptr<Stage>& stage,const shared_ptr<Player>& owner) :
		//		GameObject(stage),
		//		m_owner(owner),
		//		m_dir(Vec3(-1.0f,0.0f,-1.0f).normalize()),
		//		m_MoveSpeed(1.0f),
		//		m_pickUpArea(1.0f),
		//		m_inArea(false)
		//	{
		//	}


		//	void OnCreate() override;
		//	void OnUpdate() override;
		
		//ステートマシーン
		unique_ptr< StateMachine<Item> >  m_stateMachine;
		//NearとFarを切り替える値
		float m_stateChangeSize;

		Vec3 m_itemScale;//Itemの大きさ
		Vec3 m_startPos;
		Vec3 m_itemForce;//
		Vec3 m_itemMoveSpeed;//移動速度
		float m_totalTime;
		float m_hitAfterTime;
	public:
		//構築と破棄
		Item(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
			GameObject(StagePtr),
			m_itemScale(Vec3(0.5f,0.5f,0.5f))

		{}
		virtual ~Item(){}
	public:
		const Vec3& GetForce()const {
			return m_itemForce;
		}
		void SetForce(const Vec3& f) {
			m_itemForce = f;
		}
		void AddForce(const Vec3& f) {
			m_itemForce += f;
		}
		const Vec3& GetVelocity()const {
			return m_itemMoveSpeed;
		}
		void SetVelocity(const Vec3& v) {
			m_itemMoveSpeed = v;
		}

		void ApplyForce();
		Vec3 GetTargetPos()const;

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		//ステートマシンを得る
		unique_ptr<StateMachine<Item>>& GetStateMachine() {
			return m_stateMachine;
		}
		float GetStateChangeSize() const {
			return m_stateChangeSize;
		}

		//プレイヤーとの距離を得る
		float GetToPlayerLen() const;
		//プレイヤーを追いかける行動
		void SeekPlayerBehavior();
	};

	class ItemNearState : public ObjState<Item>
	{
		ItemNearState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(ItemNearState)
			virtual void Enter(const shared_ptr<Item>& Obj)override;
		virtual void Execute(const shared_ptr<Item>& Obj)override;
		virtual void Exit(const shared_ptr<Item>& Obj)override;
	};


}//end basecross




