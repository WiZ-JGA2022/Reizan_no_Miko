/* !
@file HoldSkip.h
@brief HoldSkip
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {
	class HoldSkipSprite : public Sprites {
		const Vec2 m_DefaultSize;	//�����T�C�Y

	public:
		//�R���X�g���N�^
		HoldSkipSprite(const shared_ptr<Stage>& stage);
		//�f�X�g���N�^
		~HoldSkipSprite();

		//������
		void OnCreate() override;

	};
}
