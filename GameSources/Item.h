/*!
@file Item.h
@brief アイテムの定義
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item : public GameObject
	{
		float m_pickupRange; // プレイヤーの取得範囲

		float m_speed; // 移動速度
		int m_expValue; // 経験値量

		Vec3 m_scale; // 大きさ
		Vec3 m_position; // 位置
		Vec3 m_direction; // プレイヤーへの方向

		shared_ptr<Transform> m_transform; // トランスフォームコンポーネント

	public:
		Item(const shared_ptr<Stage>& stagePtr, const Vec3& position) :
			GameObject(stagePtr),
			m_pickupRange(0),
			m_expValue(1),
			m_scale(0.5f,0.5f,0.5f),
			m_position(position),
			m_speed(5.0f)
		{
		};
		
		void OnCreate() override;
		void OnUpdate() override;
		
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		// Expの移動処理
		void MoveExp();
	};


}//end basecross
