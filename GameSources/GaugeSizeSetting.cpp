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
		m_draw->SetTextureResource(m_TextureKey);
		SetDrawLayer((int)DrawLayer::ForeFront);

		m_transform = GetComponent<Transform>();

		//// ���ߏ�����L���ɂ���
		//SetAlphaActive(true);
	}

	void GaugeSizeSettings::SetVartices()
	{
		m_gaugeWidth = m_DefaultSize.x;

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		float u = m_uvPosition / 10.0f; // uv�̈ʒu�𒲐�

		// ���_�f�[�^�̐ݒ�
		m_vertices = {
			{Vec3(0.0f			 , 0.0f			  , 0.0f), white, Vec2(u, 0.0f)}, // ����
			{Vec3(m_DefaultSize.x, 0.0f			  , 0.0f), white, Vec2(u + 0.1f, 0.0f)}, // �E��
			{Vec3(0.0f			 ,-m_DefaultSize.y, 0.0f), white, Vec2(u, 1.0f)}, // ����
			{Vec3(m_DefaultSize.x,-m_DefaultSize.y, 0.0f), white, Vec2(u + 0.1f, 1.0f)}, // �E��
		};
	}

	void GaugeSizeSettings::UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize)
	{
		float gaugeSizeDiff = m_DefaultSize.x / gaugeSizeLimit;

		// ���_�f�[�^���X�V
		for (int i = 0; i < m_SquareVartex; i++)
		{
			if (m_TextureKey == L"HPBAR_GREEN" || m_TextureKey == L"HPBAR_RED")
			{
				float currentLostGauge = gaugeSizeLimit - currentGaugeSize;

				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = m_DefaultSize.x - gaugeSizeDiff * currentLostGauge;
				}
			}
			else
			{
				if (i % 2 == 1 && currentGaugeSize <= gaugeSizeLimit)
				{
					m_vertices[i].position.x = gaugeSizeDiff * currentGaugeSize;
				}				
			}
		}

		// �X�V���ꂽ�f�[�^�����Ƀ|���S������蒼��
		m_draw->UpdateVertices(m_vertices);
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