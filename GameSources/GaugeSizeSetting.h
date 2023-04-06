/* !
@file GaugeSizeSettings.h
@brief �e��Q�[�W�̒��_�f�[�^�Ȃǂ̐ݒ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GaugeSizeSettings : public GameObject 
	{
		// Gauge�̏����T�C�Y
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
		float m_uvShiftDistance; // 1�Q�[�W���Ƃɂ��炷UV���W�̍�

		bool m_isHp; // HP�o�[�p�̏�����EXP�o�[�p�̏��������肷��

	public:
		/**
		* GaugeSizeSettings�̃R���X�g���N�^
		*
		* @param defaultGaugeWidth : ������Ԃł̃Q�[�W�̉���
		* @param isHp : HP�o�[�Ŏg���Ȃ�true ����ȊO�Ȃ�false
		*/
		GaugeSizeSettings(const std::shared_ptr<Stage>& stage, float defaultGaugeWidth, bool isHp) :
			GameObject(stage),
			m_DefaultGaugeWidth(defaultGaugeWidth),
			m_DefaultGaugeHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(1),
			m_gaugeWidth(0),
			m_uvShiftDistance(0.1f),
			m_isHp(isHp)
		{
		}
		// ������ 
		void OnCreate() override;

		/**
		* �Q�[�W�̑傫�����X�V����֐�
		*
		* @param gaugeSizeLimit HP�܂���EXP�̏��
		* @param currentGaugeSize ���݂�HP�܂���EXP�̐�
		*/
		void UpdateGaugeSize(float gaugeSizeLimit, float currentGaugeSize);

		/**
		* �Q�[�W�̒��_�f�[�^��ݒ肷��֐�
		*/
		void SetVartices();

		/**
		* �Q�[�W�̕\���ʒu��ݒ肷��֐�
		*
		* @param pos �\���������ʒu(Vec3�^)
		* @param h Y���W�̌W��
		*/
		virtual void SetPosition(const Vec3& pos, float h);

		/**
		* �Q�[�W�̕\���ʒu��ݒ肷��֐�
		*
		* @param pos �\���������ʒu(Vec2�^)
		* @param h Y���W�̌W��
		*/
		virtual void SetPosition(const Vec2& pos, float h)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f), h);
		}

		/**
		* �Q�[�W�̕\���ʒu��ݒ肷��֐�
		*
		* @param pos : �\���������ʒu(float�^)
		* @param h : Y���W�̌W��
		*/
		void SetPosition(float x, float y, float h)
		{
			SetPosition(Vec2(x, y), h);
		}

		/**
		* �Q�[�W�̉������擾����֐�
		*
		* @return �Q�[�W�̉���
		*/
		float GetGaugeSize()
		{
			return m_gaugeWidth;
		}
	};
}