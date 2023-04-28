/* !
@file StartButtonUI.h
@brief �^�C�g���V�[���̃X�^�[�g�{�^��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StartSprite : public Sprites {
		const Vec2 m_DefaultSize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		StartSprite(const shared_ptr<Stage>& stage);
		~StartSprite();

		void OnCreate() override;
	};
}
