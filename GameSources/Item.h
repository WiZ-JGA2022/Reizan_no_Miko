/*!
@file Item.h
@brief �A�C�e���̒�`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Item : public GameObject
	{
		float m_pickupRange; // �v���C���[�̎擾�͈�

		float m_speed; // �ړ����x
		int m_expValue; // �o���l��

		Vec3 m_scale; // �傫��
		Vec3 m_position; // �ʒu
		Vec3 m_direction; // �v���C���[�ւ̕���

		shared_ptr<Transform> m_transform; // �g�����X�t�H�[���R���|�[�l���g

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

		// Exp�̈ړ�����
		void MoveExp();
	};


}//end basecross
