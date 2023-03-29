/*!
@file Item.cpp
@brief �A�C�e���̎���
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

		//Item�̃R���|�[�l���g�ݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(0.5f));//�傫��
		transComp->SetPosition(1.0f, 0.0f, 0.0f);//�ʒu

		////�Փ˔��������
		//auto PtrCol = AddComponent<CollisionObb>();
		////�Փ˔����None�ɂ���
		//PtrCol->SetAfterCollision(AfterCollision::None);

		////�����v�Z�{�b�N�X
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(true);


		////�X�e�[�g�}�V���̍\�z
		//m_stateMachine.reset(new StateMachine<Item>(GetThis<Item>()));

	}

	//void Item::OnUpdate()
	//{		
		//auto& app = App::GetApp();

		////�f���^�^�C�����擾
		//float delta = app->GetElapsedTime();

		//auto transComp = GetComponent<Transform>();
		//Vec3 Itempos = transComp->GetPosition();
		//Itempos += m_MoveSpeed * m_dir * delta;
		//transComp->SetPosition(Itempos);
		

		//�v���C���[�����̋������ɗ����炻�̕��Ɉړ�����
		//if ()
		//{
		//	

		//}

		////Item���v���C���[�̋߂��ɗ��������
		//if (Itempos.length() <1.0f && m_owner)//�܂�player�̔���͂ł��ĂȂ��̂�1.0�����Ă���
		//{
		//	GetStage()->RemoveGameObject<Item>(GetThis<Item>());
		//}


	//}	
	//�X�V
	//void Item::OnUpdate() 
	//{
	//	//�X�e�[�g�}�V����Update���s��
	//		//���̒��ŃX�e�[�g�̐؂�ւ����s����
	//		m_stateMachine->Update();
	//}

	//�v���C���[�Ƃ̋����𓾂�
	float Item::GetToPlayerLen() const {
		auto Ptr = GetComponent<Transform>();
		Vec3 Pos = Ptr->GetPosition();
		auto PlayerPos
			= GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
		return length(Pos - PlayerPos);
	}
	//�v���C���[��ǂ�������s��
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
