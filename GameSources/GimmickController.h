/*!
@file GimmickController.h
@brief �M�~�b�N���o���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GimmickController : public GameObject {
		
		Vec3 m_position;

		shared_ptr<Transform> m_transform;

	public :
		GimmickController(const shared_ptr<Stage>& stage);
		~GimmickController();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
