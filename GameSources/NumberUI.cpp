/**
@file NumberUI.cpp
@brief �e��p�����[�^�Ɏg�p���鐔���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NumberUI::NumberUI(const shared_ptr<Stage>& stage, const Vec2& spriteSize, const wstring& spriteKey) :
		GameObject(stage),
		m_SpriteWidth(spriteSize.x),
		m_SpriteHeight(spriteSize.y),
		m_SpriteColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_spriteKey(spriteKey),
		m_number(0)
	{
	}
	NumberUI::~NumberUI() {}

	void NumberUI::OnCreate()
	{
		float uv = m_number / m_SpriteNumber;

		m_vertices = {
			{Vec3(0.0f			, 0.0f			, 0.0f), m_SpriteColor, Vec2(uv						, 0.0f)}, // ����
			{Vec3(m_SpriteWidth	, 0.0f			, 0.0f), m_SpriteColor, Vec2(uv + m_SpriteUvPosition, 0.0f)}, // �E��
			{Vec3(0.0f			,-m_SpriteHeight, 0.0f), m_SpriteColor, Vec2(uv						, 1.0f)}, // ����
			{Vec3(m_SpriteWidth	,-m_SpriteHeight, 0.0f), m_SpriteColor, Vec2(uv + m_SpriteUvPosition, 1.0f)}, // �E��
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

	void NumberUI::SetPosition(const Vec3& pos)
	{
		auto& app = App::GetApp();

		// ��ʂ̕��ƍ������擾����
		auto w = app->GetGameWidth();
		auto h = app->GetGameHeight();

		m_transform->SetPosition(Vec3(pos.x - (w * 0.5f), -pos.y + h * 0.5f, pos.z));
	}

	void NumberUI::SetPosition(const Vec2& pos)
	{
		SetPosition(Vec3(pos.x, pos.y, 0.0f));
	}

	void NumberUI::SetPosition(float x, float y)
	{
		SetPosition(Vec2(x, y));
	}

}