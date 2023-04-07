/*!
@file GimmicController.h
@brief ギミックを出すクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GimmicController : public GameObject {
	public :
		GimmicController(const shared_ptr<Stage>& stage);
		~GimmicController();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
