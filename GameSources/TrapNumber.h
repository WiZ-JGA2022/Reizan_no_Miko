/**
@file TrapNumber.h
@brief 㩂�u���鐔�𐔎��ŕ\������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TrapNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f); // �����T�C�Y

		int m_place; // ��

		vector<shared_ptr<NumberUI>> m_numbers[4]; // �i���o�[�I�u�W�F�N�g

	public:
		// �R���X�g���N�^
		TrapNumber(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~TrapNumber();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
		// �`�揈��
		void OnDraw() override;

		/**
		* �����̍X�V����
		* 
		* @param trapLimit 㩂̏���̎擾 		
		* @param currentTrapCount �������Ă�g���b�v�̐�
		* @param index �X�V�������w��
		* 
		**/
		void UpdateValue(int trapLimit, int currentTrapCount, int index);
	};
}
