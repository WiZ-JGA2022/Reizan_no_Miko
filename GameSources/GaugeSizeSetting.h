/* !
@file GaugeSizeSetting.h
@brief �e��Q�[�W�̒��_�f�[�^�Ȃǂ̐ݒ�
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class GaugeSizeSetting : public GameObject 
	{
		// HpBar�̏����T�C�Y
		const float m_DefaultGaugeWidth;
		const float m_DefaultGaugeHeight;
		// ���_�̐�
		const int m_SquareVartex;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

		int m_uvPosition; // �\�������ʒu��\���l
		float m_gaugeWidth; // ��P�ʖ��ɐL�΂��E���炷�Q�[�W�̉���

	public:
		// �R���X�g���N�^ //
		GaugeSizeSetting(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultGaugeWidth(400.0f),
			m_DefaultGaugeHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(0),
			m_gaugeWidth(0)
		{
		}
		// ������ //
		void OnCreate() override;

		// UV�̏ꏊ�����߂�֐� //
		void SetGaugeSize(float gaugeSizeLimit, float currentGaugeSize);

		// 2D���W�w��ŃX�v���C�g�̈ʒu��ݒ肷��֐� //
		virtual void SetPosition(const Vec3& pos, float h);

		// 2D���W�w��ŃX�v���C�g�̈ʒu��ݒ肷��֐��iVec2�o�[�W�����j//
		virtual void SetPosition(const Vec2& pos, float h)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f), h);
		}

		// 2D���W�w��ŃX�v���C�g�̈ʒu��ݒ肷��֐��ifloat�o�[�W�����j//
		void SetPosition(float x, float y, float h)
		{
			SetPosition(Vec2(x, y), h);
		}
	};
}