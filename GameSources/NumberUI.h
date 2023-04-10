/**
@file NumberUI.h
@brief �e��p�����[�^�Ɏg�p���鐔���̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class NumberUI : public GameObject {
		// �傫��
		const int m_SpriteWidth;
		const int m_SpriteHeight;
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
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey);
		~NumberUI();

		void OnCreate() override;
		
		void SetNumber(int number);

		void SetPosition(const Vec3& pos, float h);
		void SetPosition(const Vec2& pos, float h);
		void SetPosition(float x, float y, float h);
	};
}