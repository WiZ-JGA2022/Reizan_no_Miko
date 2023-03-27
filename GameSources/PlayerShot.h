/*!
@file Player.h
@brief �v���C���[�Ȃ�
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

		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V
		void OnPushX();
	};
	////--------------------------------------------------------------------------------------
	////	�C�e�ɓ��������X�e�[�g
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
	///	�C�e
	//--------------------------------------------------------------------------------------
	class FireSphere : public GameObject {
		Vec3 m_Emitter;
		Vec3 m_Velocity;
		float m_Scale;
		float m_ActiveMaxY;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	Emitter	���ˈʒu
		@param[in]	Velocity	���x
		*/
		//--------------------------------------------------------------------------------------
		FireSphere(const shared_ptr<Stage>& StagePtr,
			const Vec3& Emitter, const Vec3& Velocity
		);
		virtual ~FireSphere();
		//������
		void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(const CollisionPair& Pair) override;
		//���̂����Z�b�g����
		void Reset(const Vec3& Emitter, const Vec3& Velocity);
	};

}
