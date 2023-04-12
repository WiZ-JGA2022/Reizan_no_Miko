/**
@file TimeChara.h
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeChara : public GameObject {
		const Vec2 m_UiSize = Vec2(128.0f, 25.6f);

		Vec3 m_position;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;
	public :
		TimeChara(const shared_ptr<Stage>& stage);
		~TimeChara();

		void OnCreate();
	};
}