/**
@file TrapNumber.h
@brief 㩂�u���鐔�𐔎��ŕ\������UI
*/

#pragma once
#include "stdafx.h"
#include "NumberUI.h"

namespace basecross {
	class TrapNumber : public GameObject {

		const Vec2 m_Size = Vec2(24.0f, 48.0f);

		int m_place;

		float m_maxHp;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^
		vector<shared_ptr<NumberUI>> m_numbers[4];

	public:
		// �R���X�g���N�^
		TrapNumber(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~TrapNumber();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����
		void OnDraw() override; // �`�揈��

		void UpdateValue(int trapLimit, int currentTrapCount, int index);
	};
}
