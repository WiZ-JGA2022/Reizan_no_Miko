/**
@file StandbySprite.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StandbySprite : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

	public:
		// �R���X�g���N�^
		StandbySprite(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~StandbySprite();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����

	};
}