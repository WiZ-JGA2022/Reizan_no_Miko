/*!
@file EffectController.h
@brief エフェクト
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
