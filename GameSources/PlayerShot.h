/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerShot : public GameObject
	{

	public:
		PlayerShot(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnUpdate() override; // �I�u�W�F�N�g�f�[�^�̍X�V
	};


}
