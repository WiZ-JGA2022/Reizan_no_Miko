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
		unique_ptr< StateMachine<Item> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_HitAfterTime;
	public:
		//�\�z�Ɣj��
		Item(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
			GameObject(StagePtr)
		{}
		virtual ~Item()
		{}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		//�X�e�[�g�}�V���𓾂�
		const unique_ptr<StateMachine<Item>>& GetStateMachine() {
			return m_StateMachine;
		}
		//�v���C���[�Ƃ̋����𓾂�
		float GetToPlayerLen() const;
		//�v���C���[��ǂ�������s��
		void SeekPlayerBehavior();
	};
}//end basecross




