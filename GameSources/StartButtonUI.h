/* !
@file StartButtonUI.h
@brief �^�C�g���V�[���̃X�^�[�g�{�^��
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class StartSprite : public Sprites {
		const Vec2 m_DefaultSize;//�����T�C�Y

		bool m_changeSpeed; //�{�^���������ꂽ��_�ő��x�ύX�t���O

	public:
		//�R���X�g���N�^
		StartSprite(const shared_ptr<Stage>& stage);
		//�f�X�g���N�^
		~StartSprite();

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;

	};
}
