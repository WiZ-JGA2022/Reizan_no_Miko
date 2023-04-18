/* !
@file TrapUI.h
@brief �g���b�vUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class TrapSprite : public GameObject {
		const Vec2 m_DefaultSize = Vec2(150.0f, 150.0f);;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		TrapSprite(const shared_ptr<Stage>& stage);
		~TrapSprite();

		void OnCreate() override;
	};
}