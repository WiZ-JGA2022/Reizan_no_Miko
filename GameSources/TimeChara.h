/**
@file TimeChara.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class TimeChara : public Sprites {
		const Vec2 m_DefaultSize; // �����T�C�Y

	public :
		// �R���X�g���N�^
		TimeChara(const shared_ptr<Stage>& stage);
		// �f�X�g���N�^
		~TimeChara();

		void OnCreate() override; // ������
		void OnUpdate() override; // �X�V����


	};
}