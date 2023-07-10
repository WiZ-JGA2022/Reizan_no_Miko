/**
@file NumberUI.cpp
@brief �e��p�����[�^�Ɏg�p���鐔���̎���
@prod ��I�t
@detail �w�ǂ̏����͎��ƃT���v�����Q�l�ɂ��܂����B
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NumberUI::NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey) :
		Sprites(stage),
		m_DefaultSize(spriteSize),
		m_SpriteColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_SpriteNumber(11.0f),
		m_SpriteUvPosition(0.09f),
		m_spriteKey(spriteKey),
		m_number(0)
	{
	}
	NumberUI::~NumberUI() {}

	void NumberUI::OnCreate()
	{
		m_vertices = {
			{Vec3(0.0f				, 0.0f				, 0.0f), m_SpriteColor, Vec2(0				   , 0.0f)}, // ����
			{Vec3(m_DefaultSize.x	, 0.0f				, 0.0f), m_SpriteColor, Vec2(m_SpriteUvPosition, 0.0f)}, // �E��
			{Vec3(0.0f				,-m_DefaultSize.y	, 0.0f), m_SpriteColor, Vec2(0				   , 1.0f)}, // ����
			{Vec3(m_DefaultSize.x	,-m_DefaultSize.y	, 0.0f), m_SpriteColor, Vec2(m_SpriteUvPosition, 1.0f)}, // �E��
		};

		m_indices = {
			0, 1, 2, // ����̎O�p(�|���S��)
			2, 1, 3  // �E���̎O�p(�|���S��)
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_spriteKey);

		m_transform = GetComponent<Transform>();

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
		SetDrawLayer((int)DrawLayer::ForeFront);
	}

	void NumberUI::SetNumber(int number)
	{
		m_number = number;

		// ���_�f�[�^���X�V�iUV���W���w��̃i���o�[�̈ʒu�ɂ��炷�j
		m_vertices[0].textureCoordinate.x = m_number / m_SpriteNumber;						// ����
		m_vertices[1].textureCoordinate.x = m_number / m_SpriteNumber + m_SpriteUvPosition; // �E��
		m_vertices[2].textureCoordinate.x = m_number / m_SpriteNumber;						// ����
		m_vertices[3].textureCoordinate.x = m_number / m_SpriteNumber + m_SpriteUvPosition;	// �E��

		// �X�V���ꂽ�f�[�^�����Ƀ|���S������蒼��
		m_draw->UpdateVertices(m_vertices);
	}

	void NumberUI::SetPosition(const Vec3& pos, float h)
	{
		auto& app = App::GetApp();

		// ��ʂ̕��ƍ������擾����
		auto width = app->GetGameWidth();
		auto height = app->GetGameHeight();

		m_transform->SetPosition(Vec3(pos.x - (width * 0.5f), -pos.y + height * h, pos.z));
	}

	void NumberUI::SetPosition(const Vec2& pos, float h)
	{
		SetPosition(Vec3(pos.x, pos.y, 0.0f), h);
	}

	void NumberUI::SetPosition(float x, float y, float h)
	{
		SetPosition(Vec2(x, y), h);
	}

}