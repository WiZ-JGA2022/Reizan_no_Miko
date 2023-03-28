/* !
@file HpBar.h
@brief �v���C���[�̗̑͂�\������o�[
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class HpBar : public GameObject
	{
		// HpBar�̏����T�C�Y
		const float m_DefaultHpBarWidth;
		const float m_DefaultHpBarHeight;
		// ���_�̐�
		const int m_SquareVartex;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// Bar��UV���W���w�肷��z��
		vector<shared_ptr<HpBar>> m_bar;

		int m_uvPosition; // �\�������ʒu��\���l
		float m_HpBarWidth; // 1Hp���ɐL�΂�HpBar�̉���
		float m_uvShiftDistance;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		HpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultHpBarWidth(400.0f),
			m_DefaultHpBarHeight(24.0f),
			m_SquareVartex(4),
			m_uvPosition(0),
			m_HpBarWidth(0),
			m_uvShiftDistance(0.1f)
		{
		}

		// ������ //
		void OnCreate() override;
		// �X�V���� //
		void OnUpdate() override;
		// �`�揈�� //
		void OnDraw() override;

		// UV�̏ꏊ�����߂�֐� //
		void SetUvPosition(int number, float HpLimit, int HpLv);

		// �|���S���̒��_�ʒu��ݒ肷��֐� //
		void SetVartices(float HpLimit);

		// 2D���W�w��ŃX�v���C�g�̈ʒu��ݒ肷��֐� //
		virtual void SetPosition(const Vec3& pos);

		// 2D���W�w��ŃX�v���C�g�̈ʒu��ݒ肷��֐��iVec2�o�[�W�����j
		virtual void SetPosition(const Vec2& pos)
		{
			SetPosition(Vec3(pos.x, pos.y, 0.0f));
		}

		void SetPosition(float x, float y)
		{
			SetPosition(Vec2(x, y));
		}

	};
}
//end basecross

