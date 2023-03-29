/*!
@file GaugeSizeSettings.cpp
@brief �e��Q�[�W�̒��_�f�[�^�Ȃǂ̐ݒ�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GaugeSizeSettings::OnCreate()
	{
		SetVartices();

		m_indices = {
			0, 1, 2, // ����̎O�p(�|���S��)
			2, 1, 3  // �E���̎O�p(�|���S��)
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		if (m_isHp)
		{
			m_draw->SetTextureResource(L"HPBAR_GREEN");
		}
		else
		{
			m_draw->SetTextureResource(L"EXPBAR_BLUE");
		}

		m_transform = GetComponent<Transform>();

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
	}

	void GaugeSizeSettings::SetVartices()
	{
		m_gaugeWidth = m_DefaultGaugeWidth; // 1exp������̃o�[�̑傫�����v�Z

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		float u = m_uvPosition / 10.0f; // uv�̈ʒu�𒲐�

		// ���_�f�[�^�̐ݒ�
		m_vertices = {
			{Vec3(0.0f, 0.0f, 0.0f), white, Vec2(u, 0.0f)}, // ����
			{Vec3(m_gaugeWidth, 0.0f, 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // �E��
			{Vec3(0.0f,-m_DefaultGaugeHeight, 0.0f), white, Vec2(u, 1.0f)}, // ����
			{Vec3(m_gaugeWidth,-m_DefaultGaugeHeight, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // �E��
		};
	}

	void GaugeSizeSettings::UpdateGaugeSize(float gaugeSizeLimit, float currentGaugeSize)
	{
		float gaugeSizeDiff = m_DefaultGaugeWidth / gaugeSizeLimit;

		// ���_�f�[�^���X�V
		for (int i = 0; i < m_SquareVartex; i++)
		{
			if (m_isHp)
			{
				float currentLostGauge = gaugeSizeLimit - currentGaugeSize;

				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = m_DefaultGaugeWidth - gaugeSizeDiff * currentLostGauge;
				}
			}
			else
			{
				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = gaugeSizeDiff * currentGaugeSize;
				}				
			}

			//if (i % 2 == 0)
			//{
			//	m_vertices[i].textureCoordinate.x = m_uvPosition / gaugeSizeLimit;
			//}
			//else
			//{
			//	m_vertices[i].textureCoordinate.x = m_uvPosition / gaugeSizeLimit + (m_uvShiftDistance / statusLevel);
			//}
		}

		// �X�V���ꂽ�f�[�^�����Ƀ|���S������蒼��
		m_draw->UpdateVertices(m_vertices);
	

		// �f�o�b�O�p������ //
		//auto& app = App::GetApp();
		//wstringstream wss;
		//auto scene = app->GetScene<Scene>();
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());
		// �����܂� //
	}

	void GaugeSizeSettings::SetPosition(const Vec3& pos, float h)
	{
		auto& app = App::GetApp();

		// ��ʂ̕��ƍ������擾����
		auto width = app->GetGameWidth();
		auto height = app->GetGameHeight();

		m_transform->SetPosition(Vec3(-pos.x + (width * 0.5f), -pos.y + (height * h), pos.z)); // ��ʔ��������炵�Č��_����ʍ���ɂ��炷�B�܂��AY���W�͉������ɔ��]������
	}

}