/**
@file StandbySprite.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StandbySprite : public Sprites {
		const Vec2 m_DefaultSize = Vec2(384.0f, 64.0f);

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public:
		StandbySprite(const shared_ptr<Stage>& stage);
		~StandbySprite();

		void OnCreate();
	};
}