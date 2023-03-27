/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerShot : public GameObject
	{

	public:
		PlayerShot(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnUpdate() override; // オブジェクトデータの更新
		void OnPushX();
	};
	////--------------------------------------------------------------------------------------
	////	砲弾に当たったステート
	////--------------------------------------------------------------------------------------
	//class BoxHitState : public ObjState<PlayerController>
	//{
	//	BoxHitState() {}
	//public:
	//	static shared_ptr<BoxHitState> Instance();
	//	virtual void Enter(const shared_ptr<PlayerController>& Obj)override;
	//	virtual void Execute(const shared_ptr<PlayerController>& Obj)override;
	//	virtual void Exit(const shared_ptr<PlayerController>& Obj)override;
	//};

	//--------------------------------------------------------------------------------------
	///	砲弾
	//--------------------------------------------------------------------------------------
	class FireSphere : public GameObject {
		Vec3 m_Emitter;
		Vec3 m_Velocity;
		float m_Scale;
		float m_ActiveMaxY;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	Emitter	発射位置
		@param[in]	Velocity	速度
		*/
		//--------------------------------------------------------------------------------------
		FireSphere(const shared_ptr<Stage>& StagePtr,
			const Vec3& Emitter, const Vec3& Velocity
		);
		virtual ~FireSphere();
		//初期化
		void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(const CollisionPair& Pair) override;
		//物体をリセットする
		void Reset(const Vec3& Emitter, const Vec3& Velocity);
	};

}
