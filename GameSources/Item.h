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
		unique_ptr< StateMachine<Item> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_HitAfterTime;
	public:
		//構築と破棄
		Item(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
			GameObject(StagePtr)
		{}
		virtual ~Item()
		{}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		//ステートマシンを得る
		const unique_ptr<StateMachine<Item>>& GetStateMachine() {
			return m_StateMachine;
		}
		//プレイヤーとの距離を得る
		float GetToPlayerLen() const;
		//プレイヤーを追いかける行動
		void SeekPlayerBehavior();
	};
}//end basecross




