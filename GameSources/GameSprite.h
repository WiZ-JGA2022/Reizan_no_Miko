/**
@file GameSprite.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class GameSprite : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y
		const Vec2 m_AfterSize; // �X�V�T�C�Y

		Vec3 m_position; // �e�N�X�`����

	public:
		// �R���X�g���N�^
		GameSprite(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~GameSprite();

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

	};
}