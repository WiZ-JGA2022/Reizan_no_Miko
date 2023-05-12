/*!
@file EffectController.h
@brief �G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectController : public GameObject
	{


	public:
		EffectController(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override;
	};

}
