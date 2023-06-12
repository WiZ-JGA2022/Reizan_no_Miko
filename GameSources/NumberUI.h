/**
@file NumberUI.h
@brief �e��p�����[�^�Ɏg�p���鐔���̎���
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class NumberUI : public Sprites {
		// �傫��
		const Vec2 m_DefaultSize;
		// �F
		const Col4 m_SpriteColor;
		// �X�v���C�g�̐��Ƃ��炷UV���W
		const float m_SpriteNumber = 11.0f;
		const float m_SpriteUvPosition = 0.09f;

		// �\������鐔����\���l
		int m_number;

		// �g�p����X�v���C�g�̖��O
		wstring m_spriteKey;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �p�ɂɎg�p����R���|�[�l���g���������ăA�N�Z�X���₷������
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public :
		// �R���X�g���N�^
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey);
		// �f�X�g���N�^
		~NumberUI();

		void OnCreate() override; // ������
		
		void SetNumber(int number); // 

		void SetPosition(const Vec3& pos, float h); //
		void SetPosition(const Vec2& pos, float h); //
		void SetPosition(float x, float y, float h); //
	};
}