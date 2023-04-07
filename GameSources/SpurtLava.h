/*!
@file SpurtLava.h
@brief •¬o‚·‚é—nŠâ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpurtLava : public GameObject {

		shared_ptr<Transform> m_transform;
	public:
		SpurtLava(const shared_ptr<Stage>& stage);
		~SpurtLava();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
