/*!
@file ExpBar.cpp
@brief �o���l��\������o�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ExpBar::OnCreate()
	{
		SetVartices(30.0f); // ������expLimit�ɂ���

		m_indices = {
			0, 1, 2, // ����̎O�p(�|���S��)
			2, 1, 3  // �E���̎O�p(�|���S��)
		};

		m_bar.reserve(30);

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"EXPBAR_BLUE");

		m_transform = GetComponent<Transform>();

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
	}

	// �X�V���� //
	void ExpBar::OnUpdate()
	{
		SetVartices(30.0f); // ������expLimit�ɂ���

		for (int i = 0; i < 30; i++) // �J��Ԃ��񐔂��擾����exp�̐��ɂ���(int�^�ɃL���X�g����)
		{
			auto barObj = ObjectFactory::Create<ExpBar>(GetStage()); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
			barObj->SetPosition(App::GetApp()->GetGameWidth() - m_expBarWidth * i, 0.0f); // ��ʂ̍��[����E�[�Ɍ������ăQ�[�W��L�΂�
			barObj->SetUvPosition(i, 30.0f, 3); // ��������expLimit�ɁA��O������expLv�ɂ���
			m_bar.push_back(barObj); // �I�u�W�F�N�g��z��ɒǉ�
		}
	}

	// �`�揈�� //
	void ExpBar::OnDraw()
	{
		for (auto& bar : m_bar)
		{
			bar->GameObject::OnDraw();
		}
	}

	// �\������UV���W���w�肷�� //
	void ExpBar::SetUvPosition(int number, float expLimit, int expLv)
	{
		m_uvPosition = number;

		// ���_�f�[�^���X�V�iUV���W���w��̈ʒu�ɂ��炷�j
		for (int i = 0; i < m_SquareVartex; i++)
		{
			if (i % 2 == 0)
			{
				m_vertices[i].textureCoordinate.x = m_uvPosition / expLimit;
			}
			else
			{
				m_vertices[i].textureCoordinate.x = m_uvPosition / expLimit + (m_uvShiftDistance / expLv);
			}
		}

		// �X�V���ꂽ�f�[�^�����Ƀ|���S������蒼��
		m_draw->UpdateVertices(m_vertices);
	}

	// �|���S���̒��_�ʒu��ݒ肷��֐� //
	void ExpBar::SetVartices(float expLimit)
	{
		m_expBarWidth = m_DefaultExpBarWidth / expLimit; // 1exp������̃o�[�̑傫�����v�Z

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		float u = m_uvPosition / 10.0f; // uv�̈ʒu�𒲐�

		// ���_�f�[�^�̐ݒ�
		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f), white, Vec2(u, 0.0f)}, // ����
			{Vec3(m_expBarWidth, 0.0f, 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // �E��
			{Vec3(0.0f,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u, 1.0f)}, // ����
			{Vec3(m_expBarWidth,-m_DefaultExpBarHeight, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // �E��
		};
	}
	
	// �\���ʒu�̐ݒ� //
	void ExpBar::SetPosition(const Vec3& pos)
	{
		auto& app = App::GetApp();

		// ��ʂ̕��ƍ������擾����
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		m_transform->SetPosition(Vec3(-pos.x + (w * 0.5f), -pos.y + h * 0.46f, pos.z)); // ��ʔ��������炵�Č��_����ʍ���ɂ��炷�B�܂��AY���W�͉������ɔ��]������
	}

}
//end basecross
