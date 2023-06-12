/**
@file HpNumber.h
@brief ����HP�ƍő�HP�𐔎��ŕ\������UI
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class HpNumber : public GameObject {
		
		const Vec2 m_Size = Vec2(12.0f, 24.0f); // �����T�C�Y
		
		int m_place; // 

		float m_maxHp; // 

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^
		vector<shared_ptr<NumberUI>> m_numbers;

	public :
		// �R���X�g���N�^
		HpNumber(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~HpNumber();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����
		void OnDraw() override; // �`�揈��

		void UpdateValue(int maxHp, float currentHp); // 
	};
}