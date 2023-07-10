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
		const Vec2 m_DefaultSize; // �傫��
		const Col4 m_SpriteColor; // �F

		// �X�v���C�g�̐��Ƃ��炷UV���W
		const float m_SpriteNumber;
		const float m_SpriteUvPosition;
		
		int m_number; // �\������鐔����\���l

		wstring m_spriteKey; // �g�p����X�v���C�g�̖��O

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �g�����X�t�H�[���R���|�[�l���g�ƃh���[�R���|�[�l���g
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public :
		// �R���X�g���N�^
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey);
		// �f�X�g���N�^
		~NumberUI();

		// ������
		void OnCreate() override;

		// �\�����鐔���̐ݒ�
		void SetNumber(int number); 

		/**
		* �����̕\���ʒu��ݒ肷��֐�
		*
		* @param pos �\���������ʒu(Vec3�^)
		* @param h Y���W�̌W��
		*/
		void SetPosition(const Vec3& pos, float h);

		/**
		* �����̕\���ʒu��ݒ肷��֐�
		*
		* @param pos �\���������ʒu(Vec2�^)
		* @param h Y���W�̌W��
		*/
		void SetPosition(const Vec2& pos, float h);

		/**
		* �����̕\���ʒu��ݒ肷��֐�
		*
		* @param x : �\��������x���W
		* @param y : �\��������y���W
		* @param h : Y���W�̌W��
		*/
		void SetPosition(float x, float y, float h);
	};
}