/*!
@file Item.h
@brief �A�C�e���̒�`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item : public GameObject {

		//	std::shared_ptr<Transform> m_transform;

		//	Vec3 m_dir;//�ړ�����
		//	float m_MoveSpeed;//�ړ����x
		//	float m_pickUpArea;//�|�b�v����͈�
		//	bool m_inArea;//�v���C���[�̎擾���鎞�̃t���O

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
		
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<Item> >  m_stateMachine;
		//Near��Far��؂�ւ���l
		float m_stateChangeSize;

		Vec3 m_itemScale;//Item�̑傫��
		Vec3 m_startPos;
		Vec3 m_itemForce;//
		Vec3 m_itemMoveSpeed;//�ړ����x
		float m_totalTime;
		float m_hitAfterTime;
	public:
		//�\�z�Ɣj��
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

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		//�X�e�[�g�}�V���𓾂�
		unique_ptr<StateMachine<Item>>& GetStateMachine() {
			return m_stateMachine;
		}
		float GetStateChangeSize() const {
			return m_stateChangeSize;
		}

		//�v���C���[�Ƃ̋����𓾂�
		float GetToPlayerLen() const;
		//�v���C���[��ǂ�������s��
		void SeekPlayerBehavior();
	};

	class ItemNearState : public ObjState<Item>
	{
		ItemNearState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(ItemNearState)
			virtual void Enter(const shared_ptr<Item>& Obj)override;
		virtual void Execute(const shared_ptr<Item>& Obj)override;
		virtual void Exit(const shared_ptr<Item>& Obj)override;
	};


}//end basecross




