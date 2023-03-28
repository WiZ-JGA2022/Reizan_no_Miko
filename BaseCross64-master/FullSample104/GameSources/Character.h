/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//class MultiSpark : public MultiParticle;
	//用途: 複数のスパーククラス
	//--------------------------------------------------------------------------------------
	class MultiSpark : public MultiParticle {
	public:
		//構築と破棄
		MultiSpark(shared_ptr<Stage>& StagePtr);
		virtual ~MultiSpark();
		//初期化
		virtual void OnCreate() override;
		//スパーク送出
		void InsertSpark(const Vec3& Pos);
	};

	//--------------------------------------------------------------------------------------
	///	ボックス
	//--------------------------------------------------------------------------------------
	class Box : public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<Box> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_HitAfterTime;
	public:
		//構築と破棄
		Box(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Box();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		//ステートマシンを得る
		const unique_ptr<StateMachine<Box>>& GetStateMachine() {
			return m_StateMachine;
		}
		//プレイヤーとの距離を得る
		float GetToPlayerLen() const;
		//砲弾にヒットした後の時間を加算する（現在のヒット後の時間を返す）
		float AddHitAfterTime();
		//速度を0にする
		void Stop();
		//行ったり来たりの行動
		void GoFromBehavior();
		//プレイヤーを追いかける行動
		void SeekPlayerBehavior();
		//砲弾発射行動
		void FirShellBehavior(int div, float up);
		//砲弾が当たった行動
		void FirShellHitBehavior(const Vec3& HitVelocity);
	};

	//--------------------------------------------------------------------------------------
	//	通常移動
	//--------------------------------------------------------------------------------------
	class BoxDefaultState : public ObjState<Box>
	{
		BoxDefaultState() {}
	public:
		static shared_ptr<BoxDefaultState> Instance();
		virtual void Enter(const shared_ptr<Box>& Obj)override;
		virtual void Execute(const shared_ptr<Box>& Obj)override;
		virtual void Exit(const shared_ptr<Box>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	追いかける通常攻撃ステート
	//--------------------------------------------------------------------------------------
	class BoxSimpleAttackState : public ObjState<Box>
	{
		BoxSimpleAttackState() {}
	public:
		static shared_ptr<BoxSimpleAttackState> Instance();
		virtual void Enter(const shared_ptr<Box>& Obj)override;
		virtual void Execute(const shared_ptr<Box>& Obj)override;
		virtual void Exit(const shared_ptr<Box>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	ハードな攻撃ステート
	//--------------------------------------------------------------------------------------
	class BoxHradAttackState : public ObjState<Box>
	{
		BoxHradAttackState() {}
	public:
		static shared_ptr<BoxHradAttackState> Instance();
		virtual void Enter(const shared_ptr<Box>& Obj)override;
		virtual void Execute(const shared_ptr<Box>& Obj)override;
		virtual void Exit(const shared_ptr<Box>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	砲弾に当たったステート
	//--------------------------------------------------------------------------------------
	class BoxHitState : public ObjState<Box>
	{
		BoxHitState() {}
	public:
		static shared_ptr<BoxHitState> Instance();
		virtual void Enter(const shared_ptr<Box>& Obj)override;
		virtual void Execute(const shared_ptr<Box>& Obj)override;
		virtual void Exit(const shared_ptr<Box>& Obj)override;
	};



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
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(const CollisionPair& Pair) override;
		//物体をリセットする
		void Reset(const Vec3& Emitter, const Vec3& Velocity);
	};


	//--------------------------------------------------------------------------------------
	///	物理計算する固定のボックス
	//--------------------------------------------------------------------------------------
	class FixedPsBox : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedPsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~FixedPsBox();
		//初期化
		virtual void OnCreate() override;
	};


	//--------------------------------------------------------------------------------------
	///	物理計算するアクティブなオブジェクトの親
	//--------------------------------------------------------------------------------------
	class ActivePsObject : public GameObject {
		bool m_Selected;
	protected:
		ActivePsObject(const shared_ptr<Stage>& StagePtr) :
			GameObject(StagePtr), m_Selected(false) {}
		virtual ~ActivePsObject() {}
	public:
		void SetSelected(bool b) {
			m_Selected = b;
			auto PtrDraw = AddComponent<BcPNTStaticDraw>();
			if (b) {
				PtrDraw->SetEmissive(Col4(1.0f, 1.0f, 0, 0));

			}
			else {
				PtrDraw->SetEmissive(Col4(0.0f, 0.0f, 0, 0));
			}

		}
		bool IsSelected() {
			return m_Selected;
		}
		//更新
		virtual void OnUpdate() override;
	};


	//--------------------------------------------------------------------------------------
	///	物理計算するアクティブなボックス
	//--------------------------------------------------------------------------------------
	class ActivePsBox : public ActivePsObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		ActivePsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsBox();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	///	物理計算するアクティブな球体
	//--------------------------------------------------------------------------------------
	class ActivePsSphere : public ActivePsObject {
		float m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		ActivePsSphere(const shared_ptr<Stage>& StagePtr,
			float Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsSphere();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	///	物理計算するアクティブなカプセル
	//--------------------------------------------------------------------------------------
	class ActivePsCapsule : public ActivePsObject {
		//長さ
		float m_Len;
		//直径
		float m_Diameter;
		Quat m_Qt;
		Vec3 m_Position;
		//メッシュ（カプセルは各オブジェクトが保持）
		shared_ptr<MeshResource> m_CapsuleMesh;
	public:
		//構築と破棄
		ActivePsCapsule(const shared_ptr<Stage>& StagePtr,
			float Len,
			float Diameter,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsCapsule();
		//初期化
		virtual void OnCreate() override;
	};




}
//end basecross
